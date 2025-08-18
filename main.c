#include "headers.h"
#include "fileio.c"

int main(int argc, char *argv[]){
    /*
        Testing File I/O Operations
    */

    // Writing 1011 (binary)
    FILE *out = fopen("test.bin", "wb");
    write_bit(out, 1);
    write_bit(out, 0);
    write_bit(out, 1);
    write_bit(out, 1);
    write_bit(out, 0);
    write_bit(out, 1);
    write_bit(out, 0);
    write_bit(out, 1);
    
    write_bit(out, 1);
    write_bit(out, 1);
    flush_bits(out);
    fclose(out);

    // Reading from the same file
    FILE *in = fopen("test.bin", "rb");
    int b;
    while ((b = read_bit(in)) != EOF) {
        printf("%d", b);
    }
    fclose(in);

    return 0;
}