#include "headergen_tree.h"

#include <stdio.h>
#include <stdlib.h>

headergen_node_t *headergen_tree_add_sibling(headergen_node_t *base)
{
    headergen_node_t *current_sibling = base;
    headergen_node_t *next_sibling = current_sibling->sibling;

    while (next_sibling != NULL)
    {
        current_sibling = next_sibling; 
        next_sibling = current_sibling->sibling;            
    }

    headergen_node_t *sibling = malloc(sizeof(headergen_node_t));
    current_sibling->sibling = sibling;
    return sibling;
}

headergen_node_t *headergen_tree_add_child(headergen_node_t *base)
{
    if (base->child == NULL)
    {
        headergen_node_t *child = malloc(sizeof(headergen_node_t));
        base->child = child;
        return child; 
    }
    else
    {
        return headergen_tree_add_sibling(base->child);
    }          
}

void headergen_tree_delete_siblings(headergen_node_t *base)
{
    headergen_node_t *next_sibling;
    headergen_node_t *current_sibling;

    current_sibling = base;

    while (current_sibling != NULL)
    {
        next_sibling = current_sibling->sibling;
        free(current_sibling);
        current_sibling = next_sibling;
    }
}

void headergen_tree_delete_children(headergen_node_t *base)
{
    headergen_node_t *current_child;

    current_child = base->child;

    if (current_child != NULL)
    {
        headergen_tree_delete_children(current_child);  

        if (current_child != base) 
        {
            headergen_tree_delete_siblings(current_child);
        }
    }

    base->child = NULL;
}

static int count = 0;

static void headergen_tree_traverse_recurse(headergen_node_t *base, int depth)
{
    headergen_node_t *current_sibling = base;
    int breadth = 0;

    while (current_sibling != NULL)
    {
        printf("%d:\tC%dS%d\n", count, depth, breadth);

        count++;

        if (current_sibling->child != NULL)
        {
            headergen_tree_traverse_recurse(current_sibling->child, depth + 1);     
        }

        current_sibling = current_sibling->sibling;
        breadth++;      
    }  
}

void headergen_tree_traverse(headergen_node_t *base)
{
    int depth = 0;
    count = 0;
    printf("Traversing tree:\n");
    headergen_tree_traverse_recurse(base, depth);
}