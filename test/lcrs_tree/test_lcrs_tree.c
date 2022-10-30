
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "lcrs_tree.h"

int main(void) 
{
    struct lcrs_node root = {.child = NULL, .sibling = NULL, .info = NULL};

    struct lcrs_node *c = lcrs_tree_add_child(&root, 1);
    struct lcrs_node *cs = lcrs_tree_add_sibling(c, 1);
    struct lcrs_node *css = lcrs_tree_add_sibling(c, 1);
    struct lcrs_node *cssc = lcrs_tree_add_child(css, 1);
    struct lcrs_node *csc = lcrs_tree_add_child(cs, 1);
    struct lcrs_node *cscs = lcrs_tree_add_sibling(csc, 1);
    struct lcrs_node *cscss = lcrs_tree_add_sibling(csc, 1);

    lcrs_tree_traverse(&root);

    lcrs_tree_delete_children_recursive(&root);

    printf("Deleted\n");

    lcrs_tree_traverse(&root);

    struct lcrs_node *s = lcrs_tree_add_sibling(&root, 1);
    struct lcrs_node *sc = lcrs_tree_add_child(s, 1);

    lcrs_tree_traverse(&root);

    printf("Done\n");

    return 0;
}