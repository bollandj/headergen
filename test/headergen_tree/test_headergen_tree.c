
#include <stdio.h>
#include <assert.h>

#include "headergen_tree.h"

int main(void) 
{
    headergen_node_t c0s0 = {0};
    headergen_node_t *c0s0_p = &c0s0;

    headergen_node_t *c1s0_p = headergen_tree_add_child(c0s0_p);
    assert(c1s0_p == c0s0_p->child);
    headergen_node_t *c1s1_p = headergen_tree_add_child(c0s0_p);
    assert(c1s1_p == c1s0_p->sibling);
    headergen_node_t *c1s2_p = headergen_tree_add_sibling(c1s0_p);
    assert(c1s2_p == c1s1_p->sibling);
    headergen_node_t *c1s3_p = headergen_tree_add_child(c0s0_p);
    assert(c1s3_p == c1s2_p->sibling);

    headergen_node_t *c2s0_c1s0_p = headergen_tree_add_child(c1s0_p);
    assert(c2s0_c1s0_p == c1s0_p->child);
    headergen_node_t *c2s1_c1s0_p = headergen_tree_add_child(c1s0_p);
    assert(c2s1_c1s0_p == c2s0_c1s0_p->sibling);

    headergen_node_t *c2s0_c1s1_p = headergen_tree_add_child(c1s1_p);
    assert(c2s0_c1s1_p == c1s1_p->child);
    headergen_node_t *c2s1_c1s1_p = headergen_tree_add_sibling(c2s0_c1s1_p);
    assert(c2s1_c1s1_p == c2s0_c1s1_p->sibling);
    headergen_node_t *c2s2_c1s1_p = headergen_tree_add_sibling(c2s1_c1s1_p);
    assert(c2s2_c1s1_p == c2s1_c1s1_p->sibling);

    headergen_node_t *c3s0_c2s0_c1s0_p = headergen_tree_add_child(c2s0_c1s0_p);
    assert(c3s0_c2s0_c1s0_p == c2s0_c1s0_p->child);

    headergen_node_t *c3s0_c2s1_c1s0_p = headergen_tree_add_child(c2s1_c1s0_p);
    assert(c3s0_c2s1_c1s0_p == c2s1_c1s0_p->child);

    headergen_node_t *c3s0_c2s0_c1s1_p = headergen_tree_add_child(c2s0_c1s1_p);
    assert(c3s0_c2s0_c1s1_p == c2s0_c1s1_p->child);

    headergen_node_t *c3s0_c2s2_c1s1_p = headergen_tree_add_child(c2s2_c1s1_p);
    assert(c3s0_c2s2_c1s1_p == c2s2_c1s1_p->child);
    headergen_node_t *c3s1_c2s2_c1s1_p = headergen_tree_add_child(c2s2_c1s1_p);
    assert(c3s1_c2s2_c1s1_p == c3s0_c2s2_c1s1_p->sibling);

    headergen_node_t *c4s0_c3s0_c2s2_c1s1_p = headergen_tree_add_child(c3s0_c2s2_c1s1_p);
    assert(c4s0_c3s0_c2s2_c1s1_p == c3s0_c2s2_c1s1_p->child);

    headergen_tree_traverse(c0s0_p);
    headergen_tree_delete_children(c1s1_p);
    headergen_tree_traverse(c0s0_p);

    return 0;
}