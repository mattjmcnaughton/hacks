#ifndef constants_h
#define constants_h

#include <stdint.h>

#define TABLE_MAX_PAGES 100
extern const uint32_t PAGE_SIZE;

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;
extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;
extern const uint32_t ROW_SIZE;

/**
 * Each node corresponds to one page. So when we save `pages` to the db, we are
 * now saving nodes in our btree.
 * Internal nodes point to their children by storing the page number that stores the child.
 * The btree asks the pager for a particular page number and gets back a pointer
 * into the page cache. Pages are stored in the database file one after the
 * other in order of page number.
 */

/**
 * Nodes store the following metadata:
 * - The type of node it is.
 * - Whether it is a root node.
 * - The pointer to its parent.
 */
extern const uint32_t NODE_TYPE_SIZE;
extern const uint32_t NODE_TYPE_OFFSET;
extern const uint32_t IS_ROOT_SIZE;
extern const uint32_t IS_ROOT_OFFSET;
extern const uint32_t PARENT_POINTER_SIZE;
extern const uint32_t PARENT_POINTER_OFFSET;
extern const uint8_t COMMON_NODE_HEADER_SIZE;

/**
 * In addition to the common header fields, leaf nodes need to store how many
 * "cells" they contain. A cell is a key/value pair.
 */
extern const uint32_t LEAF_NODE_NUM_CELLS_SIZE;
extern const uint32_t LEAF_NODE_NUM_CELLS_OFFSET;
extern const uint32_t LEAF_NODE_HEADER_SIZE;

/**
 * The body of a leaf node is an array of cells. Each cell is a key followed by
 * a value (a serialized row).
 */

extern const uint32_t LEAF_NODE_KEY_SIZE;
extern const uint32_t LEAF_NODE_KEY_OFFSET;
extern const uint32_t LEAF_NODE_VALUE_SIZE;
extern const uint32_t LEAF_NODE_VALUE_OFFSET;
extern const uint32_t LEAF_NODE_CELL_SIZE;
extern const uint32_t LEAF_NODE_SPACE_FOR_CELLS;
extern const uint32_t LEAF_NODE_MAX_CELLS;

#endif
