#pragma once

#include <stdint.h>

#include "headergen_types.h"

/**
 * Implementation of a dynamically allocated first child next sibling tree
 */

typedef struct headergen_node headergen_node_t;

struct headergen_node {

    headergen_node_t *sibling;
    headergen_node_t *child;

    union {
        headergen_root_t root;
        headergen_dev_t dev;
        headergen_reg_t reg;
        headergen_fld_t fld;
        headergen_opt_t opt;
    };

};

/** Allocate memory for a new node and add it as a sibling to the base node */
headergen_node_t *headergen_tree_add_sibling(headergen_node_t *base);

/** Allocate memory for a new node and add it as a child to the base node */
headergen_node_t *headergen_tree_add_child(headergen_node_t *base);

/** Delete all siblings of the base node, as well as the base node itself */
void headergen_tree_delete_siblings(headergen_node_t *base);

/** Recursively delete all children of the base node, not including the base node */
void headergen_tree_delete_children(headergen_node_t *base);

/** Traverse the tree starting from the base node, depth-first*/
void headergen_tree_traverse(headergen_node_t *base);
