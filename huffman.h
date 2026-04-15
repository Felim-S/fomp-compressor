/*
Uses Huffman Encoding to compress the input file and store the result in the output file
@param input file to be compressed
@param output the compressed file
*/
void huffman_compress(FILE *input, FILE *output);
/*
Uses Huffman Encoding to decompress the input file and store the result in the output file
@param input file to be decompressed
@param output the decompressed file
*/
void huffman_decompress(FILE *input, FILE *output);