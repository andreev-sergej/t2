#include "memory.h"
#include "func.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char **memory_allocation(Tree *tree) 
{
    char **memory = malloc(tree->height * sizeof(char *));
    for (int i = 0; i < tree->height; i++) 
    {
        memory[i] = malloc(sizeof(char) * tree->width);
        for (int j = 0; j < tree->width; j++)
        {
            memory[i][j] = ' ';
        }
    }
    return memory;
}


void memory_put_char(char c, char **memory, int y, int x) 
{
    memory[y][x] = c;
}

void memory_put_number(int number, char **memory, int y, int x) 
{
    int temp = number;
    for (int i = 0; i < get_number_length(number); i++) 
    {
        memory_put_char(temp%10 + '0', memory, y, x + get_number_length(number) - i - 1);
        temp /= 10;
    }
}

void memory_fill(Tree *tree) 
{
    int pos_x = 0;
    for (int i = 0; i < tree->first_level_length; i++) 
    {
        node_to_memory(tree->nodes[i], 0, pos_x, V, tree->memory);
        if (i != tree->first_level_length - 1) 
        {
            for (int j = get_number_length(tree->nodes[i]->data); j < tree->nodes[i]->rect_width + 1; j++) 
            {
                memory_put_char('-', tree->memory, 0, pos_x + j);
            }
            pos_x += tree->nodes[i]->rect_width + 1;
        }
    }
}

void memory_free(char **memory, int height) 
{
    for (int i = 0; i < height; i++) 
    {
        free(memory[i]);
    }
    free(memory);
}
