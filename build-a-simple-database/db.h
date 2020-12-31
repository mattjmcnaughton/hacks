#ifndef db_h
#define db_h

#include "table.h"

Table *db_open(const char *filename);
void db_close(Table * table);

#endif
