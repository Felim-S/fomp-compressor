/*
Uses RLE (Run-Length Encoding) to compress the input file and store the result in the output file
@param input file to be compressed
@param output the compressed file
*/
void rle_compress(FILE *input, FILE *output);
/*
Uses RLE (Run-Length Encoding) to decompress the input file and store the result in the output file
@param input file to be decompressed
@param output the decompressed file
*/
void rle_decompress(FILE *input, FILE *output);