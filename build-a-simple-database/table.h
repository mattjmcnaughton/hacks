#ifndef table_h
#define table_h

#include <stdint.h>

#include "constants.h"
#include "pager.h"

typedef struct {
    uint32_t id;
    // Add the extra byte to allow the string to end with a null byte.
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

typedef struct {
    Pager *pager;
    // A table is identified by its root node page number.
    uint32_t root_page_num;
} Table;

void print_row(Row * row);
void serialize_row(Row * source, void *destination);
void deserialize_row(void *source, Row * destination);

#endif
