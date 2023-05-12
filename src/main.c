#include <stdio.h>
#include "tree.h"
#include "memory.h"
#include "test.h"

int main() 
{
    run_all_tests();

    int chain_start = 0, chain_end = 0;
    printf("Start of the chain: ");
    if (scanf("%d", &chain_start) == EOF)
        return 1;
    if (chain_start < 0) 
    {
        printf("Less than 0!");
        return 1;
    }

    printf("\nEnd of the chain: ");
    if (scanf("%d", &chain_end) == EOF)
        return 1;
    if (chain_end < 0) 
    {
        printf("Less than 0!");
        return 1;
    }
    
    if (chain_start > chain_end)
    {
        printf("End value is less than start value\n");
        return 1;
    }

    Tree *tree = tree_create(chain_start, chain_end);
    memory_fill(tree);
    tree_print(tree);
    tree_print_to_file(tree, "output.txt");
    tree_free(tree);
    return 0;
}