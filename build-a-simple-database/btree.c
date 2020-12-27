#include <stdint.h>

#include "btree.h"
#include "constants.h"

/**
 * The following four functions are pointer arithmetic to access keys, values,
 * and metadatas for leaf nodes and their cells.
 */
uint32_t* leaf_node_num_cells(void* node) {
    return node + LEAF_NODE_NUM_CELLS_OFFSET;
}

void* leaf_node_cell(void* node, uint32_t cell_num) {
    return node + LEAF_NODE_HEADER_SIZE + cell_num * LEAF_NODE_CELL_SIZE;
}

uint32_t* leaf_node_key(void* node, uint32_t cell_num) {
    return leaf_node_cell(node, cell_num);
}

void* leaf_node_value(void* node, uint32_t cell_num) {
    return leaf_node_cell(node, cell_num) + LEAF_NODE_KEY_SIZE;
}

void initialize_leaf_node(void* node) {
    // Since `leaf_node_num_cells` returns a pointer, it can be used as both a
    // getter and a setter.
    *leaf_node_num_cells(node) = 0;
}