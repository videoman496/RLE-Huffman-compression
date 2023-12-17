#define MAX_SZ 128
#define MAX_CODE_LEN 64

char codes[MAX_SZ][MAX_CODE_LEN];
typedef struct Node {
    char character;
    int count;
    struct Node *left;
    struct Node *right;
} Node;
void calculate_prob(char *str, int *counts);
int comparator(const void *a, const void *b);
Node *find_and_remove_min(Node *nodes, int sz);
void dfs(Node *node, char *path, int sz);
char *fileToString(char *file_name, long *size);
void writeCodeBook(FILE* file);
void writeBitToFile(unsigned char bit, FILE *file, int flush);
void decompress(FILE *inputFile, Node *root, FILE *outputFile, long originalSize);
void compressUsingRLE(char* inputFile, char* outputFile);
void decompressUsingRLE( char* inputFile,  char* outputFile);
