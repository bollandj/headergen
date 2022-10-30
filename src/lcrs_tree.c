#include "lcrs_tree.h"

#include <stdint.h>
#include <stdlib.h>

/* Allocate memory for a new node and its associated data and initialise struct members */
static struct lcrs_node *lcrs_tree_create_node(size_t info_size)
{
    struct lcrs_node *new_node = malloc(sizeof(struct lcrs_node));

    new_node->child = NULL;
    new_node->sibling = NULL;
    new_node->info = malloc(info_size);
    
    return new_node;
}

/* Deallocate memory used by a node and its associated data */
static void lcrs_tree_delete_node(struct lcrs_node *node)
{
    free(node->info);
    free(node);   
}

/* Delete all children of a node non-recursively */
static void lcrs_tree_delete_children(struct lcrs_node *base)
{
    struct lcrs_node *current_sibling = base->child;
    struct lcrs_node *next_sibling;

    while (current_sibling != NULL)
    {
        next_sibling = current_sibling->sibling;
        lcrs_tree_delete_node(current_sibling);
        current_sibling = next_sibling;
    }

    base->child = NULL;
}

struct lcrs_node *lcrs_tree_add_sibling(struct lcrs_node *base, size_t info_size)
{
    struct lcrs_node *current_sibling = base;
    struct lcrs_node *next_sibling = current_sibling->sibling;

    while (next_sibling != NULL)
    {
        current_sibling = next_sibling; 
        next_sibling = current_sibling->sibling;            
    }

    struct lcrs_node *new_sibling = lcrs_tree_create_node(info_size);   
    current_sibling->sibling = new_sibling;

    return new_sibling;
}

struct lcrs_node *lcrs_tree_add_child(struct lcrs_node *base, size_t info_size)
{
    if (base->child == NULL)
    {
        struct lcrs_node *new_child = lcrs_tree_create_node(info_size); 
        base->child = new_child;
        return new_child; 
    }
    else
    {
        // Node already has at least one child - add new node as a sibling to current children
        return lcrs_tree_add_sibling(base->child, info_size);
    }          
}

void lcrs_tree_delete_children_recursive(struct lcrs_node *base)
{
    struct lcrs_node *current_sibling = base->child;

    while (current_sibling != NULL)
    {
        lcrs_tree_delete_children_recursive(current_sibling); 
        current_sibling = current_sibling->sibling;           
    } 

    lcrs_tree_delete_children(base);
}

static int count = 0;

static void lcrs_tree_traverse_recurse(struct lcrs_node *base, int depth)
{
    struct lcrs_node *current_sibling = base;
    int breadth = 0;

    while (current_sibling != NULL)
    {
        printf("%d:\tC%dS%d\n", count, depth, breadth);

        count++;

        if (current_sibling->child != NULL)
        {
            lcrs_tree_traverse_recurse(current_sibling->child, depth + 1);     
        }

        current_sibling = current_sibling->sibling;
        breadth++;      
    }  
}

void lcrs_tree_traverse(struct lcrs_node *base)
{
    int depth = 0;
    count = 0;
    printf("Traversing tree:\n");
    lcrs_tree_traverse_recurse(base, depth);
}