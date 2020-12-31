#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "btree.h"
#include "constants.h"
#include "db.h"
#include "pager.h"

/**
 * TMP: Since we do not yet support splitting a root node, our db is current
 * limited to a single node.
 */
Table *db_open(const char *filename)
{
    Pager *pager = pager_open(filename);

    Table *table = malloc(sizeof(Table));
    table->pager = pager;
    table->root_page_num = 0;

    if (pager->num_pages == 0) {
        // New dtabase file. Initialize page 0 as leaf node.
        void *root_node = get_page(pager, 0);
        initialize_leaf_node(root_node);
    }

    return table;
}

void db_close(Table * table)
{
    Pager *pager = table->pager;

    for (uint32_t i = 0; i < pager->num_pages; i++) {
        if (pager->pages[i] == NULL) {
            // No need to flush empty pages
            continue;
        }

        pager_flush(pager, i);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }

    // Each node gets exactly one page, so we don't need to worry about writing
    // partial pages to the file.

    int result = close(pager->file_descriptor);
    if (result == -1) {
        printf("Error closing db file.\n");
        exit(EXIT_FAILURE);
    }
    // TODO: Need to investigate more around why this is necessary... aren't we
    // flushing all of the pages? We do set `pages[i]` to be NULL after flushing
    // and freeing, so not a risk of "double freeing".
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        void *page = pager->pages[i];
        if (page) {
            free(page);
            pager->pages[i] = NULL;
        }
    }

    free(pager);
    free(table);
}
