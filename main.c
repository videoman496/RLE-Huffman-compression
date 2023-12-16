#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "compressor.c"
int result;
int counts[128];

int main(int argc, char* argv[]) {
    

    char *algorithm = argv[1];
    char *input_file_name = argv[2];
    char *output_file_name = argv[3]; 

    if (strcmp(algorithm, "-h") == 0) {
        long file_size;
        char *str = fileToString(argv[2], &file_size); 
        if (!str) {
            printf("Failed to read input file.\n");
            return 1;
        }

        //  Calculating character probabilities
        calculate_prob(str, counts);

        // Building Huffman Tree
        int node_count = 0;
        for (int i = 0; i < MAX_SZ; i++) {
            if (counts[i] != 0) node_count++;
        }

        Node nodes[node_count];
        int idx = 0;
        for (int i = 0; i < MAX_SZ; i++) {
            if (counts[i] != 0) {
                nodes[idx++] = (Node) {.character = (char) i, .count = counts[i], .left = NULL, .right = NULL};
            }
        }

        qsort(nodes, node_count, sizeof(Node), comparator);

        while (node_count > 1) {
            Node *min1 = find_and_remove_min(nodes, node_count--);
            Node *min2 = find_and_remove_min(nodes, node_count--);
            nodes[node_count++] = (Node) {.character = '\0', .count = min1->count + min2->count, .left = min1, .right = min2};
        }
        Node *root = &nodes[0];

        // Generating Huffman codes
        char path[MAX_CODE_LEN] = {0};
        dfs(root, path, 0);

        //  Writing compressed file
        FILE *compressedFile = fopen(argv[3], "w");
        if (!compressedFile) {
            printf("Failed to open compressed file for writing.\n");
            return 1;
        }

        writeCodeBook(compressedFile);
        for (char *s = str; *s; s++) {
            char *code = codes[(unsigned char) *s];
            for (int i = 0; code[i]; i++) {
                writeBitToFile(code[i] - '0', compressedFile, 0);
            }
        }
        writeBitToFile(0, compressedFile, 1); 
        fclose(compressedFile);

        // Reading and decompressing the file
        compressedFile = fopen(argv[3], "rb");
        if (!compressedFile) {
            printf("Failed to open compressed file for reading.\n");
            return 1;
        }

        FILE *decompressedFile = fopen(argv[4], "w");
        if (!decompressedFile) {
            printf("Failed to open decompressed file for writing.\n");
            fclose(compressedFile);
            return 1;
        }

        decompress(compressedFile, root, decompressedFile, file_size); 
        fclose(compressedFile);
        fclose(decompressedFile);
        free(str);
        printf("Compression and decompression completed.\n");

        if (result != 0) {
            fprintf(stderr, "Compression using Huffman failed\n");
            return 1;
        }

    }
    if (strcmp(algorithm, "-r") == 0) {
        if(strcmp(argv[2],"-c")==0){
            compressUsingRLE(argv[3], "RLECompressed.txt");
        }
        else if (strcmp(argv[2],"-d")==0){
            decompressUsingRLE("RLECompressed.txt", "RLEDecompressed.txt");
        }


        if (result != 0) {
            fprintf(stderr, "Compression using RLE failed\n");
            return 1;
        }
        printf("Compression using RLE completed successfully\n");
    } else {
        fprintf(stderr, "Invalid algorithm. Use -h for Huffman or -r for RLE.\n");
        return 1;
    }

    return 0;
}
