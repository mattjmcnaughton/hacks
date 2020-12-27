#ifndef meta_h
#define meta_h

#include "input_buffer.h"
#include "table.h"

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);

// TODO: I only need to declare functions in the header that are "public" (i.e.
// might be accessed from other files). These functions, for example, are not
// public. Do a full sweep of the program.
void print_constants();
void print_leaf_node(void* node);

#endif
