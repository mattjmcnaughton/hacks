#ifndef cursor_h
#define cursor_h

#include <stdbool.h>
#include <stdint.h>

#include "table.h"

typedef struct {
  Table* table;
  // Our cursor represents a position in the table. Now that our table is
  // represented via a b-tree, we identify a position by the page number of the
  // node, and the cell number within that node.
  uint32_t page_num;
  uint32_t cell_num;
  bool end_of_table; // Indicates a position one past the last element.
} Cursor;

Cursor* table_start(Table* table);
Cursor* table_end(Table* table);
void *cursor_value(Cursor* cursor);
void cursor_advance(Cursor* cursor);

#endif
