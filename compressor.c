#include "compressor.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
void compressUsingRLE(char* inputFile,  char* outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (in == NULL || out == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int head = fgetc(in);
    if (head == EOF) {
        fclose(in);
        fclose(out);
        return;
    }

    int count = 1;
    while(1) {
        int next = fgetc(in);
        if (next == EOF || next != head) {
            if (count > 1) {
                fprintf(out, "%c%d", head, count);
            } else {
                fputc(head, out);
            }
            if (next == EOF) break;
            head = next;
            count = 1;
        } else {
            count++;
        }
    }

    fclose(in);
    fclose(out);
}

void decompressUsingRLE( char* inputFile, char* outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");
    if (in == NULL || out == NULL) {
        perror("Error opening file");
        exit(1);
    }

    while(1) {
        int head = fgetc(in);
        if (head == EOF) break;

        int nextChar = fgetc(in);
        if (nextChar == EOF) {
            fputc(head, out);
            break;
        }

        if (isdigit(nextChar)) {
            ungetc(nextChar, in);
            int count;
            fscanf(in, "%d", &count); 
            for (int i = 0; i < count; i++) {
                fputc(head, out);
            }
        } else {
            fputc(head, out);
            ungetc(nextChar, in); 
        }
    }

    fclose(in);
    fclose(out);
}
void calculate_prob(char *str, int *counts) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        counts[*str++]++;
    }
}

int comparator(const void *a, const void *b) {
    Node *n1 = (Node *)a;
    Node *n2 = (Node *)b;
    return (n1->count - n2->count);
}

Node *find_and_remove_min(Node *nodes, int sz) {
    int idx = 0;
    Node *minNode = &nodes[0];
    for (int i = 0; i < sz; i++) {
        if (nodes[i].count < minNode->count) {
            minNode = &nodes[i];
            idx = i;
        }
    }
    Node *node = (Node *)malloc(sizeof(Node));
    memcpy(node, minNode, sizeof(Node));
    nodes[idx] = nodes[sz - 1];
    return node;
}

void dfs(Node *node, char *path, int sz) {
    if (node == NULL) {
        return;
    }
    if (node->left == NULL && node->right == NULL) {
        strncpy(codes[node->character], path, sz);
        codes[node->character][sz] = '\0';
        return;
    }
    path[sz] = '0';
    dfs(node->left, path, sz + 1);
    path[sz] = '1';
    dfs(node->right, path, sz + 1);
}


char *fileToString(char *file_name, long *size) {
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) return NULL;

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *str = (char *)malloc(*size + 1);
    if (str == NULL) {
        fclose(file);
        return NULL;
    }

    fread(str, sizeof(char), *size, file);
    str[*size] = '\0';
    fclose(file);
    return str;
}

void writeCodeBook(FILE* file){
    for (int i = 0; i < MAX_SZ; i++) {
        if (codes[i][0] == '\0') {
            continue;
        }
    }
}

void writeBitToFile(unsigned char bit, FILE *file, int flush) {
    static int count = 0;
    static char buffer = 0;

    if(flush){
        buffer <<= (8 - count);
        fwrite(&buffer, sizeof(buffer), 1, file);
        return;
    }

    buffer <<= 1;
    if (bit) buffer |= 1; 
    count++;

    if (count == 8) {
        fwrite(&buffer, sizeof(buffer), 1, file);
        buffer = 0;
        count = 0;
    }
}
void decompress(FILE *inputFile, Node *root, FILE *outputFile, long originalSize) {
    Node *current = root;
    int ch;
    long decompressedSize = 0;
    while ((ch = getc(inputFile)) != EOF) {
        for (int i = 7; i >= 0; i--) {
            if (decompressedSize >= originalSize) {
                break;
            }
            int bit = (ch >> i) & 1;
            current = bit ? current->right : current->left;
            if (current->left == NULL && current->right == NULL) {
                putc(current->character, outputFile);
                decompressedSize++;
                current = root;
            }
        }
    }
}
