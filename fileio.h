/*
Reads in a single bit at a time from an input file.
@param file file to be read from
@return -1 if an error occured reading from the file or EOF reached, a single bit of information otherwise
*/
int read_bit(FILE *file);
/*
Writes a single bit to an input file. Flushes a byte once 8 bits are written in succession.
@param file file to be written to
@param bit data bit to be written
*/
void write_bit(FILE *file, int bit);
/*
Flushes any remaining bits written from write_bit calls (for number of bits non-divisible by 8)
@param file file to be written to
*/
void flush_bits(FILE *file);
/*
Compresses the given input file using the specified algorithm and writes the result to the output file.
@param input the file to be compressed
@param output the compressed file
@param algorithm the compression algorithm to be used
*/
void compress_file(FILE *input, FILE *output, Algorithm algorithm);
/*
Deompresses the given input file using the specified algorithm and writes the result to the output file.
@param input the file to be decompressed
@param output the decompressed file
@param algorithm the compression algorithm to be used
*/
void decompress_file(FILE *input, FILE *output, Algorithm algorithm);