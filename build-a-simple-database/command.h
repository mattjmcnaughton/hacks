#ifndef command_h
#define command_h

#include <stdint.h>
#include "cursor.h"
#include "table.h"

/**
 * Almost certainly, we could have a better name than `command` for this file.
 */

void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value);

#endif
