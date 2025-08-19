#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>

typedef enum { AUTO, RLE, HUFFMAN, LZ77 } Algorithm;

#include "fileio.h"
#include "utils.h"
#include "rle.h"