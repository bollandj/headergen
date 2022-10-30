#pragma once

#include <stddef.h>

/**
 * Implementation of a dynamically allocated left child, right sibling
 */

struct lcrs_node;

struct lcrs_node {

    struct lcrs_node *child;
    struct lcrs_node *sibling;
    
    void *info;
};

/** Allocate memory for a new node and add it as a sibling to the base node */
struct lcrs_node *lcrs_tree_add_sibling(struct lcrs_node *base, size_t info_size);

/** Allocate memory for a new node and add it as a child to the base node */
struct lcrs_node *lcrs_tree_add_child(struct lcrs_node *base, size_t info_size);

/** Recursively delete all children of the base node, not including the base node */
void lcrs_tree_delete_children_recursive(struct lcrs_node *base);

/** Traverse the tree starting from the base node, depth-first */
void lcrs_tree_traverse(struct lcrs_node *base);
