#include "compressor.h"


int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s -c|-d -h|-r input_file output_file\n", argv[0]);
        fprintf(stderr, "  -c : Compress\n");
        fprintf(stderr, "  -d : Decompress\n");
        fprintf(stderr, "  -h : Use Huffman encoding\n");
        fprintf(stderr, "  -r : Use RLE encoding\n");
        return 1;
    }

    const char *mode = argv[1];
    const char *algorithm = argv[2];
    const char *input_file_name = argv[3];
    const char *output_file_name = argv[4];

    if (strcmp(mode, "-c") == 0) {
        if (strcmp(algorithm, "-h") == 0) {
            int result = compressUsingHuffman(input_file_name, output_file_name);
            if (result != 0) {
                fprintf(stderr, "Compression using Huffman failed\n");
                return 1;
            }
            printf("Compression using Huffman completed successfully\n");
        } else if (strcmp(algorithm, "-r") == 0) {
            int result = compressUsingRLE(input_file_name, output_file_name);
            if (result != 0) {
                fprintf(stderr, "Compression using RLE failed\n");
                return 1;
            }
            printf("Compression using RLE completed successfully\n");
        } else {
            fprintf(stderr, "Invalid algorithm. Use -h for Huffman or -r for RLE.\n");
            return 1;
        }
    } else if (strcmp(mode, "-d") == 0) {
        if (strcmp(algorithm, "-h") == 0) {
            int result = decompressUsingHuffman(input_file_name, output_file_name);
            if (result != 0) {
                fprintf(stderr, "Decompression using Huffman failed\n");
                return 1;
            }
            printf("Decompression using Huffman completed successfully\n");
        } else if (strcmp(algorithm, "-r") == 0) {
            int result = decompressUsingRLE(input_file_name, output_file_name);
            if (result != 0) {
                fprintf(stderr, "Decompression using RLE failed\n");
                return 1;
            }
            printf("Decompression using RLE completed successfully\n");
        } else {
            fprintf(stderr, "Invalid algorithm. Use -h for Huffman or -r for RLE.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid mode. Use -c to compress or -d to decompress.\n");
        return 1;
    }

    return 0;
}
