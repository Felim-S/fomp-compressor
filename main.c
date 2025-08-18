#include "headers.h"
#include "fileio.c"
#include "utils.c"

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

    char* input = argv[optind];
    char* output = argv[optind + 1];

    printf("%s\n", compress ? "Compressing..." : "Decompressing...");
    printf("Algorithm: %s\n", algo == NULL ? "Auto" : algo);
    printf("Input: %s\n", input);
    printf("Output: %s\n", output);
    printf("\n"); // TODO - print out old file size -> new file size

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