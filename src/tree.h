#ifndef TREE
#define TREE

typedef enum {V, H} Direct;

typedef struct Node {
    int data;
    int divisors_number;
    int rect_height;
    int rect_width;
    struct Node **divisors_array;
} Node;

typedef struct Tree {
    int first_level_length;
    int height;
    int width;
    char **memory;
    Node **nodes;
} Tree;

void tree_print(Tree *tree);
void tree_print_to_file(Tree *tree, const char* path);
Node *node_create(int number, int direction);
void node_rect_size_calc(Node *node, int direction);
void node_to_memory(Node *node, int Y, int X, Direct direction, char **memory);
void node_free(Node *node);
Tree *tree_create (int chain_start, int chain_end);
void tree_free(Tree *tree);

#endif