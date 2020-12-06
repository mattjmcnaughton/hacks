#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "pager.h"

// Page size is 4kb, which is the same size as the page used in virtual memory
// systems of most architectures. One page in our db corresponds to one page
// used by the operating system. Means OS will move pages in and out of memory
// as whole units instead of breaking them up.
const uint32_t PAGE_SIZE = _PAGE_SIZE;

Pager* pager_open(const char* filename) {
    int fd = open(filename,
                  O_RDWR | // Read/write mode)
                      O_CREAT, // Create file if does not exist
                  S_IWUSR | // User write permission
                      S_IRUSR // User read permission
                  );

    if (fd == -1) {
        printf("Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    off_t file_length = lseek(fd, 0, SEEK_END);

    Pager* pager = malloc(sizeof(Pager));
    pager->file_descriptor = fd;
    pager->file_length = file_length;

    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pager->pages[i] = NULL;
    }

    return pager;
}

void* get_page(Pager* pager, uint32_t page_num) {
    if (page_num > TABLE_MAX_PAGES) {
        printf("Tried to fetch page number out of bounds. %d > %d\n", page_num, TABLE_MAX_PAGES);
        exit(EXIT_FAILURE);
    }

    if (pager->pages[page_num] == NULL) {
        // Cache miss. Allocate memory (and if possible, load data in file into
        // memory).
        void* page = malloc(PAGE_SIZE);
        // We use file_length as an indicator of what data already exists. We
        // assume that pages are saved to the file one after another.
        uint32_t num_pages = pager->file_length / PAGE_SIZE;

        // We might save a partial page at the end of the file.
        if (pager->file_length % PAGE_SIZE) {
            num_pages += 1;
        }

        // If we have data in the file, load it into memory. (I.e. populate the
        // cache). If we don't have any data, we will just return the "blank"
        // allocated memory.
        if (page_num <= num_pages) {
            lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);

            // Read PAGE_SIZE data from the file-descriptor into memory. The
            // previous call to `lseek` ensures we're reading from the correct
            // offset.
            ssize_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);
            if (bytes_read == -1) {
                printf("Error reading file: %d\n", errno);
                exit(EXIT_FAILURE);
            }
        }

        pager->pages[page_num] = page;
    }

    return pager->pages[page_num];
}

void pager_flush(Pager* pager, uint32_t page_num, uint32_t size) {
    if (pager->pages[page_num] == NULL) {
        printf("Tried to flush null page\n");
        exit(EXIT_FAILURE);
    }

    off_t offset = lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);

    if (offset == -1) {
        printf("Error seeking: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_written = write(pager->file_descriptor, pager->pages[page_num], size);

    if (bytes_written == -1) {
        printf("Error writing: %d\n", errno);
        exit(EXIT_FAILURE);
    }
}
