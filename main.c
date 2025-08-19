#include "headers.h"

int main(int argc, char *argv[]){
    
    int opt;
    char* algo = NULL; // specifies compression algorithm (-a)
    bool compress = true; // false if in decompress mode (-d)
    
    while((opt = getopt(argc, argv, "a:dh")) != -1){
        switch(opt){
            case 'a':
                algo = optarg;
                break;
            case 'd':
                compress = false;
                break;
            case 'h':
            default:
                print_usage();
                return 0;
        }
    }

    if(argc < optind + 2){
        perror("Missing input/output file(s)\n");
        return 1;
    }

    char* input_string = argv[optind];
    char* output_string = argv[optind + 1];

    Algorithm algorithm;

    if (algo == NULL) {
        algorithm = AUTO;
    } else if (strcmp(algo, "rle") == 0) {
        algorithm = RLE;
    } else if (strcmp(algo, "huffman") == 0) {
        algorithm = HUFFMAN;
    } else if (strcmp(algo, "lz77") == 0) {
        algorithm = LZ77;
    } else {
        algorithm = AUTO;
    }
    
    FILE *input = fopen(input_string, "rb");
    FILE *output = fopen(output_string, "wb");

    if(compress){
        compress_file(input, output, algorithm);
    } else{
        decompress_file(input, output, algorithm);
    }

    printf("%s\n", compress ? "Compressing..." : "Decompressing...");
    printf("Algorithm: %s\n", algo == NULL ? "Auto" : algo);
    printf("Input: %s\n", input_string);
    printf("Output: %s\n", output_string);

    fseek(input, 0L, SEEK_END);
    long input_size = ftell(input);
    fseek(output, 0L, SEEK_END);
    long output_size = ftell(output);

    printf("File Size (before compression): %ldB (bytes)\n", input_size);
    printf("File Size (after compression): %ldB (bytes)\n", output_size);

    /*
        Testing File I/O Operations
    */

    // // Writing 1011 (binary)
    // FILE *out = fopen("test.bin", "wb");
    // write_bit(out, 1);
    // write_bit(out, 0);
    // write_bit(out, 1);
    // write_bit(out, 1);
    // write_bit(out, 0);
    // write_bit(out, 1);
    // write_bit(out, 0);
    // write_bit(out, 1);
    
    // write_bit(out, 1);
    // write_bit(out, 1);
    // flush_bits(out);
    // fclose(out);

    // // Reading from the same file
    // FILE *in = fopen("test.bin", "rb");
    // int b;
    // while ((b = read_bit(in)) != EOF) {
    //     printf("%d", b);
    // }
    // fclose(in);

    return 0;
}