#include "headers.h"

/*
Note - This implementation of the RLE compression algorithm uses the following structure:
    [run length] [bit value]
    e.g. 11111000 -> [5][1] [3][0]
*/

#define MAX_BYTE_VALUE 255

void rle_compress(FILE *input, FILE *output){
    int run = 0; // stores the length of the current run
    int bit, prev; // stores the current and previous bit values
    prev = read_bit(input);
    if(prev == EOF){ return; }

    run++;
    while ((bit = read_bit(input)) != EOF) {
        if (bit == prev && run < MAX_BYTE_VALUE) {
            run++;
        } else {
            fputc(run, output); // write the run length
        
            if(bit == prev){ // same bit value, just reached max byte length
                run = 1;
            } else{ // new bit value
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
    while((run = fgetc(input)) != EOF){ // read in the run length (a byte at a time)
        for(int i = 0; i < run; i++){
            write_bit(output, bit); // write the current bit value run times
        }
        bit = !bit; // flip the bit value
    }

    flush_bits(output);
}