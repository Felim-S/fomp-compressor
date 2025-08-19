#include "headers.h"

#define MAX_BYTE_VALUE 255

void rle_compress(FILE *input, FILE *output){
    int run = 0;
    int bit, prev;
    prev = read_bit(input);
    if(prev == EOF){ return; }

    run = 1;
    while ((bit = read_bit(input)) != EOF) {
        if (bit == prev && run < MAX_BYTE_VALUE) {
            run++;
        } else {
            fputc(run, output);
        
            if(bit == prev){
                run = 1;
            } else{
                run = 1;
                prev = bit;
            }
        }
    }
    if(run > 0){
        fputc(run, output);
    }

    flush_bits(output);
}

void rle_decompress(FILE *input, FILE *output){
    int run;
    int bit = 0;
    while((run = fgetc(input)) != EOF){
        for(int i = 0; i < run; i++){
            write_bit(output, bit);
        }
        bit = !bit;
    }

    flush_bits(output);
}