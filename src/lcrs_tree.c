#include "lcrs_tree.h"

#include <stdio.h>
#include <stdlib.h>

struct lcrs_node *lcrs_tree_add_sibling(struct lcrs_node *base)
{
    struct lcrs_node *current_sibling = base;
    struct lcrs_node *next_sibling = current_sibling->sibling;

    while (next_sibling != NULL)
    {
        current_sibling = next_sibling; 
        next_sibling = current_sibling->sibling;            
    }

    struct lcrs_node *new_sibling = malloc(sizeof(struct lcrs_node));
    new_sibling->child = NULL;
    new_sibling->sibling = NULL;
    current_sibling->sibling = new_sibling;

    return new_sibling;
}

struct lcrs_node *lcrs_tree_add_child(struct lcrs_node *base)
{
    if (base->child == NULL)
    {
        struct lcrs_node *new_child = malloc(sizeof(struct lcrs_node));
        new_child->child = NULL;
        new_child->sibling = NULL;
        base->child = new_child;
        return new_child; 
    }
    else
    {
        // Node already has at least one child - add new node as a sibling to current children
        return lcrs_tree_add_sibling(base->child);
    }          
}

static void lcrs_tree_delete_siblings(struct lcrs_node *base)
{
    struct lcrs_node *next_sibling;
    struct lcrs_node *current_sibling;

    current_sibling = base;

    while (current_sibling != NULL)
    {
        next_sibling = current_sibling->sibling;
        free(current_sibling);
        current_sibling = next_sibling;
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

    lcrs_tree_delete_siblings(base->child);
    base->child = NULL;
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