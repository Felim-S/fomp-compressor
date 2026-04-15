#include "headers.h"

/* Huffman tree node */

typedef struct HuffNode {
    int symbol;             /* -1 for internal nodes */
    int freq;
    struct HuffNode *left;
    struct HuffNode *right;
} HuffNode;

static HuffNode *new_node(int symbol, int freq) {
    HuffNode *n = malloc(sizeof(HuffNode));
    if (!n) { perror("malloc"); exit(1); }
    n->symbol = symbol;
    n->freq   = freq;
    n->left   = n->right = NULL;
    return n;
}

static void free_tree(HuffNode *n) {
    if (!n) return;
    free_tree(n->left);
    free_tree(n->right);
    free(n);
}

/* Min-heap (priority queue) */

typedef struct {
    HuffNode **nodes;
    int size;
    int capacity;
} MinHeap;

static MinHeap *new_heap(int cap) {
    MinHeap *h = malloc(sizeof(MinHeap));
    if (!h) { perror("malloc"); exit(1); }
    h->nodes    = malloc(sizeof(HuffNode *) * cap);
    if (!h->nodes) { perror("malloc"); exit(1); }
    h->size     = 0;
    h->capacity = cap;
    return h;
}

static void free_heap(MinHeap *h) {
    free(h->nodes);
    free(h);
}

static void swap(HuffNode **a, HuffNode **b) {
    HuffNode *t = *a; *a = *b; *b = t;
}

static void sift_up(MinHeap *h, int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->nodes[p]->freq > h->nodes[i]->freq) {
            swap(&h->nodes[p], &h->nodes[i]);
            i = p;
        } else break;
    }
}

static void sift_down(MinHeap *h, int i) {
    for (;;) {
        int l = 2*i + 1, r = 2*i + 2, s = i;
        if (l < h->size && h->nodes[l]->freq < h->nodes[s]->freq) s = l;
        if (r < h->size && h->nodes[r]->freq < h->nodes[s]->freq) s = r;
        if (s == i) break;
        swap(&h->nodes[s], &h->nodes[i]);
        i = s;
    }
}

static void heap_push(MinHeap *h, HuffNode *n) {
    h->nodes[h->size++] = n;
    sift_up(h, h->size - 1);
}

static HuffNode *heap_pop(MinHeap *h) {
    HuffNode *min = h->nodes[0];
    h->nodes[0] = h->nodes[--h->size];
    sift_down(h, 0);
    return min;
}

/* Build Huffman tree from frequency table */

static HuffNode *build_tree(int freq[256]) {
    MinHeap *h = new_heap(512);

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0)
            heap_push(h, new_node(i, freq[i]));
    }

    /* Edge case: single unique symbol - give it code "0" */
    if (h->size == 1) {
        HuffNode *only = heap_pop(h);
        HuffNode *root = new_node(-1, only->freq);
        root->left  = only;
        root->right = new_node(only->symbol, 0);
        free_heap(h);
        return root;
    }

    while (h->size > 1) {
        HuffNode *a = heap_pop(h);
        HuffNode *b = heap_pop(h);
        HuffNode *p = new_node(-1, a->freq + b->freq);
        p->left  = a;
        p->right = b;
        heap_push(h, p);
    }

    HuffNode *root = heap_pop(h);
    free_heap(h);
    return root;
}

/* Generate codes via DFS */

/* codes[symbol] holds the bit-string, e.g. "01101" */
static void gen_codes(HuffNode *n, char *buf, int depth, char codes[256][257]) {
    if (n->symbol != -1) {
        buf[depth] = '\0';
        strcpy(codes[n->symbol], buf);
        return;
    }
    buf[depth] = '0';
    gen_codes(n->left,  buf, depth + 1, codes);
    buf[depth] = '1';
    gen_codes(n->right, buf, depth + 1, codes);
}

/* Public API */

void huffman_compress(FILE *input, FILE *output) {
    /* 1. Build frequency table */
    int freq[256] = {0};
    long file_size = 0;
    int byte;
    while ((byte = fgetc(input)) != EOF) {
        freq[byte]++;
        file_size++;
    }
    if (file_size == 0) return;

    /* 2. Write header: original size + frequency table */
    fwrite(&file_size, sizeof(long), 1, output);
    fwrite(freq, sizeof(int), 256, output);

    /* 3. Build tree and generate codes */
    HuffNode *root = build_tree(freq);
    char codes[256][257] = {{0}};
    char buf[257];
    gen_codes(root, buf, 0, codes);
    free_tree(root);

    /* 4. Encode */
    rewind(input);
    while ((byte = fgetc(input)) != EOF) {
        for (int i = 0; codes[byte][i] != '\0'; i++)
            write_bit(output, codes[byte][i] - '0');
    }
    flush_bits(output);
}

void huffman_decompress(FILE *input, FILE *output) {
    /* 1. Read header */
    long file_size;
    if (fread(&file_size, sizeof(long), 1, input) != 1) return;
    int freq[256];
    if (fread(freq, sizeof(int), 256, input) != 256) return;

    /* 2. Rebuild tree */
    HuffNode *root = build_tree(freq);

    /* 3. Decode exactly file_size symbols */
    long decoded = 0;
    HuffNode *cur = root;
    int bit;
    while (decoded < file_size && (bit = read_bit(input)) != -1) {
        cur = (bit == 0) ? cur->left : cur->right;
        if (cur->symbol != -1) {
            fputc(cur->symbol, output);
            decoded++;
            cur = root;
        }
    }

    free_tree(root);
}
