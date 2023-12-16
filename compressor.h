#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SZ 128
#define MAX_CODE_LEN 64

// Объявление структуры Node
typedef struct Node {
    char character;
    int count;
    struct Node *left;
    struct Node *right;
} Node;

// Объявления функций сжатия и декомпрессии
int compressUsingHuffman(const char* input_file_name, const char* output_file_name);
int decompressUsingHuffman(const char* input_file_name, const char* output_file_name);
int compressUsingRLE(const char* inputFile, const char* outputFile);
int decompressUsingRLE(const char* inputFile, const char* outputFile);

#endif // COMPRESSOR_H
