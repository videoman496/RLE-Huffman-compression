#include "compressor.h"
#include <ctype.h>

int counts[MAX_SZ];
char codes[MAX_SZ][MAX_CODE_LEN];



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
        codes[node->character][sz] = '\0';  // Add null terminator
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
    str[*size] = '\0'; // Null-terminate the string
    fclose(file);
    return str;
}

void writeCodeBook(FILE* file){
    for (int i = 0; i < MAX_SZ; i++) {
        if (codes[i][0] == '\0') {
            continue;
        }
        putc((char)i, file);
        putc(':', file);
        fwrite(codes[i], sizeof(char), strlen(codes[i]), file);
        putc('\n', file);
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

    buffer <<= 1;          // Make room for next bit.
    if (bit) buffer |= 1;  // Set if necessary.
    count++;

    if (count == 8) {
        fwrite(&buffer, sizeof(buffer), 1, file);  // Error handling elided.
        buffer = 0;
        count = 0;
    }
}

void decompress(FILE *inputFile, Node *root, FILE *outputFile, long originalSize) {
    Node *current = root;
    int ch;
    long decompressedSize = 0;

    while ((ch = getc(inputFile)) != EOF) {
        if (ch == '\n') {
            break; // End of codebook
        }
    }

    while ((ch = getc(inputFile)) != EOF) {
        for (int i = 7; i >= 0; i--) {
            if (decompressedSize >= originalSize) {
                break; // Stop if original file size is reached
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

int compressUsingHuffman(const char* input_file_name, const char* output_file_name) {
    long file_size;


    char *str = fileToString(input_file_name, &file_size);
    if (!str) {
        printf("Failed to read input file.\n");
        return 1;
    }

    calculate_prob(str, counts);

    int node_count = 0;
    for (int i = 0; i < MAX_SZ; i++) {
        if (counts[i] != 0) node_count++;
    }

    Node nodes[node_count];
    int idx = 0;
    for (int i = 0; i < MAX_SZ; i++) {
        if (counts[i] != 0) {
            nodes[idx++] = (Node){.character = (char)i, .count = counts[i], .left = NULL, .right = NULL};
        }
    }

    qsort(nodes, node_count, sizeof(Node), comparator);

    while (node_count > 1) {
        Node *min1 = find_and_remove_min(nodes, node_count--);
        Node *min2 = find_and_remove_min(nodes, node_count--);
        nodes[node_count++] = (Node){.character = '\0', .count = min1->count + min2->count, .left = min1, .right = min2};
    }
    Node *root = &nodes[0];

    char path[MAX_CODE_LEN] = {0};
    dfs(root, path, 0);

    FILE *compressedFile = fopen(output_file_name, "wb");
    if (!compressedFile) {
        printf("Failed to open compressed file for writing.\n");
        return 1;
    }

    writeCodeBook(compressedFile);
    for (char *s = str; *s; s++) {
        char *code = codes[(unsigned char)*s];
        for (int i = 0; code[i]; i++) {
            writeBitToFile(code[i] - '0', compressedFile, 0);
        }
    }
    writeBitToFile(0, compressedFile, 1); // Flush remaining bits
    fclose(compressedFile);

    free(str);
    return 0;
}

int decompressUsingHuffman(const char* input_file_name, const char* output_file_name) {
    FILE *inputFile = fopen(input_file_name, "rb");
    if (!inputFile) {
        printf("Failed to open input file for reading.\n");
        return 1;
    }

    FILE *outputFile = fopen(output_file_name, "wb");
    if (!outputFile) {
        fclose(inputFile);
        printf("Failed to open output file for writing.\n");
        return 1;
    }

    long originalSize; // This needs to be stored or passed to the decompression function
    decompress(inputFile, NULL, outputFile, originalSize); // The Huffman tree needs to be rebuilt or passed

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}

// ... Функции сжатия и декомпрессии RLE ...
int compressUsingRLE(const char* inputFile, const char* outputFile) {
    FILE *in = fopen(inputFile, "rb");
    if (in == NULL) {
        perror("Error opening input file");
        return 1; // Возвращает ошибку
    }

    FILE *out = fopen(outputFile, "wb");
    if (out == NULL) {
        perror("Error opening output file");
        fclose(in);
        return 1; // Возвращает ошибку
    }

    int head = fgetc(in);
    if (head == EOF) {
        fclose(in);
        fclose(out);
        return 0; // Успешное завершение при пустом файле
    }

    int count = 1;
    while (1) {
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
    return 0; // Успешное завершение
}

int decompressUsingRLE(const char* inputFile, const char* outputFile) {
    FILE *in = fopen(inputFile, "rb");
    if (in == NULL) {
        perror("Error opening input file");
        return 1; // Возвращает ошибку
    }

    FILE *out = fopen(outputFile, "wb");
    if (out == NULL) {
        perror("Error opening output file");
        fclose(in);
        return 1; // Возвращает ошибку
    }

    while (1) {
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
    return 0; // Успешное завершение
}


