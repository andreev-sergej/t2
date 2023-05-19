#include "tree.h"
#include "func.h"
#include "memory.h"
#include <math.h>
#include <stdlib.h>

Tree *tree_create (int start, int end) 
{
    Tree *tree = malloc(sizeof (Tree));
    tree->nodes = malloc((tree->first_level_length = end - start + 1) * sizeof (Node*));
    int tree_width = 0, tree_heigth = 0;
    for (int i = start; i <= end; i++) 
    {
        tree->nodes[i - start] = node_create(i, H);
        node_rect_size_calc(tree->nodes[i - start], H);
        tree_width += tree->nodes[i - start]->rect_width + 1;
        tree_heigth = max(tree_heigth, tree->nodes[i - start]->rect_height);
    }
    tree->height = tree_heigth;
    tree->width = tree_width;
    tree->memory = memory_allocation(tree);
    return tree;
}


void tree_free(Tree *tree) 
{
    memory_free(tree->memory, tree->height);
    for (int i = 0; i < tree->first_level_length; i++)
    {
        node_free(tree->nodes[i]);
    }
    free(tree->nodes);
    free(tree);
}

void tree_print(Tree *tree) 
{
    for (int i = 0; i < tree->height; i++) 
    {
        for (int j = 0; j < tree->width; j++) 
        {
            printf("\033[1m\033[36m%c\033[0m", tree->memory[i][j]);
        }
        putchar('\n');
    }
}

void tree_print_to_file(Tree *tree, const char *filename) 
{
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < tree->height; i++) 
    {
        for (int j = 0; j < tree->width; j++) 
        {
            fprintf(file, "%c", tree->memory[i][j]);
        }
        fputc('\n', file);
    }
    fclose(file);
}

Node *node_create(int data, int dir) 
{
    Node *node = malloc(sizeof(Node));

    int divisors_number = get_divisors_number(data);

    node->data = data;
    node->divisors_number = divisors_number;
    node->rect_height = 1;
    node->rect_width = get_number_length(data);

    if (divisors_number == 0) 
    {
        node->divisors_array = NULL;
        return node;
    }
    int sqrt_int = ((int) sqrt(data)) + 1;
    node->divisors_array = malloc(node->divisors_number * sizeof(Node *));
    int divisors_index = 0;
    for (int i = 2; i < sqrt_int; i++) 
    {
        if (data % i == 0) 
        {
            (node->divisors_array)[divisors_index] = node_create(i, !dir);
            if (data != i * i) 
            {
                (node->divisors_array)[divisors_number - divisors_index - 1] = node_create(data / i, !dir);
            }
            divisors_index++;
        }
    }
    return node;
}

void node_rect_size_calc(Node *node, int dir) 
{
    if (node->divisors_number == 0) 
        return;
    int max_heigth = -1, max_width = -1;
    for (int i = 0; i < (node->divisors_number); i++) 
    {
        node_rect_size_calc((node->divisors_array)[i], !dir);
        if (dir == V) 
        {
            node->rect_width += 1 + (node->divisors_array)[i]->rect_width;
            max_heigth = max(max_heigth, (node->divisors_array)[i]->rect_height);
        } 
        else 
        {
            node->rect_height += 1 + (node->divisors_array)[i]->rect_height;
            max_width = max(max_width, (node->divisors_array)[i]->rect_width);
        }
    }
    node->rect_width = max(max_width, node->rect_width);
    node->rect_height = max(max_heigth, node->rect_height);
}

void node_to_memory(Node *node, int y, int x, Direct dir, char **memory) 
{
    memory_put_number(node->data, memory, y, x);
    if (node->divisors_number > 0) 
    {
        for (int i = 0; i < node->divisors_number; i++) 
        {
            Node *new_node = node->divisors_array[i];
            Node *prev_node;
            if (i != 0) 
            {
                prev_node = node->divisors_array[i - 1];
            }

            if (dir == H) {
                if (i == 0) 
                {
                    x += get_number_length(node->data);
                }
                else
                {
                    for (int j = get_number_length(prev_node ->data); j < prev_node -> rect_width + 1; j++) 
                    {
                        memory_put_char('-', memory, y, x + j);
                    }
                    x += prev_node -> rect_width;
                }
                memory_put_char('-', memory, y, x);
            } 
            else 
            {
                if (i == 0) memory_put_char('|', memory, ++y, x);
                else 
                {
                    for (int j = 0; j < prev_node->rect_height; j++) 
                    {
                        memory_put_char('|', memory, ++y, x);
                    }
                }
            }

            if (dir == V)
            {
                y++;
                node_to_memory(new_node, y, x, H, memory);
            }
            else
            {
                x++;
                node_to_memory(new_node, y, x, V, memory);
            }
            //node_to_memory(new_node,(y += 1 - dir),(x += dir), !dir, memory); //переписать
        }
    }
}


void node_free(Node *node)
{
    if (node->divisors_number != 0) 
    {
        for (int i = 0; i < node->divisors_number; i++) 
        {
            if ((node->divisors_array)[i]->divisors_number != 0) 
            {
                node_free((node->divisors_array)[i]);
            } 
            else 
            {
                free(node->divisors_array[i]);
            }
        }
        free(node->divisors_array);
    }
    free(node);
}

