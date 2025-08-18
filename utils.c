#include "headers.h"

void print_usage(){
    printf("Usage: fomp [-a algo] [-d] input output\n");
    printf("    -a algo     Compression algorithm (rle, huffman, lz77)\n");
    printf("    -d          Decompress mode\n");
    printf("    -h          Show this help\n");
}