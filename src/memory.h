#ifndef MEMORY
#define MEMORY

#include <stdio.h>
#include "tree.h"

char **memory_allocation(Tree *tree);
void memory_put_char(char c, char** memory, int y, int x);
void memory_put_number(int num, char **memory, int y, int x);
void memory_free(char **memory, int height);
void memory_fill(Tree *tree);

#endif