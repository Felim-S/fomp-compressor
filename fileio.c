#include "headers.h"

// Static buffer index (in order to be saved between function calls)
static char buffer = 0;
static int buffer_index = 0;

int read_bit(FILE *file){

    if(file == NULL){
        perror("Error opening file... ");
        return -1;
    }

    if(buffer_index == 0){
        // Load a single byte from the file
        int byte = fgetc(file);

        if(byte == EOF){
            return -1;
        }

        buffer = (char) byte;
        buffer_index = 8;
    }

    // Selecting MSB from the byte (this is the bit to be returned)
    // - shift over 7 places with right-shift ">> 7"    (e.g. 10110110 -> 00000001)
    // - remove padding zeros with "& 1" mask           (e.g. 00000001 -> 1)
    int bit = (buffer >> 7) & 1;
    // Shift the buffer and its index over by 1 (to prepare for the next bit)
    buffer = buffer << 1;
    buffer_index--;

    return bit;

}

void write_bit(FILE *file, int bit){

    if(file == NULL){
        perror("Error opening file... ");
        return;
    }

    // Add one bit at a time to the buffer
    // - shift left to make room for the new bit    (e.g. 01010101 -> 10101010)
    // - OR to insert new bit into "empty" position (e.g. 10101010 | 1 -> 10101011)
    // - & 1 to ensure bit is either zero or one    (avoids user errors, e.g. write_bit(file, 'a'); )
    buffer = (buffer << 1) | (bit & 1);
    buffer_index++;

    // Once 8 bits have been collected, flush the whole byte
    if(buffer_index == 8){
        fputc(buffer, file);
        // reset the buffer
        buffer = 0;
        buffer_index = 0;
    }
}

void flush_bits(FILE *file){
    // If there are remaining bits (not flushed), then flush them
    if(buffer_index > 0){
        // Pad the remaining bits with zeros
        // - calculate how many bits are left (8 - buffer_index)
        // - shift the buffer that many places left (putting the bits in the MSB position)
        // - e.g. (00000101 -> 10100000)
        buffer = buffer << (8 - buffer_index);
        fputc(buffer,file);
        // reset buffer
        buffer = 0;
        buffer_index = 0;
    }
}

void compress_file(FILE *input, FILE *output, Algorithm algorithm){
    if(input == NULL || output == NULL){
        perror("Error opening input/output file(s)... ");
        return;
    }

    if(algorithm == RLE){
        rle_compress(input, output);
    } 

}

void decompress_file(FILE *input, FILE *output, Algorithm algorithm){
    if(input == NULL || output == NULL){
        perror("Error opening input/output file(s)... ");
        return;
    }

    if(algorithm == RLE){
        rle_decompress(input, output);
    } 
    
}