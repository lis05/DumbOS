#include "memory.h"
#include "logs.h"
#include "../clib/sformat.h"
#include "../drivers/fbuff.h"

#define TOTAL_MEM (250 * (1<<20)) 
#define MEM_ADDR 0x100000
#define MEM_PTR ((char*)MEM_ADDR)
#define PAGE_SIZE 64
#define TOTAL_PAGES ((TOTAL_MEM - MEM_ADDR)/PAGE_SIZE)

#define PAGE_FREE 0
#define PAGE_USED 1

unsigned int pages[TOTAL_PAGES];

int fpages;

int is_valid_page(char *ptr) {
    if (ptr < MEM_PTR) {
        return 0;
    }
    if ((unsigned int)ptr % PAGE_SIZE != 0) {
        return 0;
    }
    return 1;
}

int ptr_to_page(char *ptr) {
    ptr -= MEM_ADDR;
    return (unsigned int)ptr / PAGE_SIZE;
}

char *page_to_ptr(int page) {
    return (char*)(page * PAGE_SIZE + MEM_ADDR);
}

void upd_page(int page, int status) {
    if (status == PAGE_FREE) {
        fpages++;
    } else {
        fpages--;
    }
    pages[page/32] &= ~(1u << (page&0x1F));
    pages[page/32] ^= (((unsigned int)status)<<(page&0x1F));
}

int get_page(int page) {
    return (pages[page/32] >> (page & 0x1F)) & 1;
}

void init_memory() {
    log_info(sprintf("Initializing memory: %i pages (%i bytes per page)\n", TOTAL_PAGES, PAGE_SIZE), BOTH);
    log_info(sprintf("pages located at: %p\n", pages), BOTH);

    fpages = 0;
    for (int i = 0; i < TOTAL_PAGES; i++) {
        upd_page(i, PAGE_FREE);
        if (i % 100 == 0 || i == TOTAL_PAGES - 1) {
            fbuff_move_cursor_to(fbuff_cursor_r(), 0);
            log_info(sprintf("Done: %i / %i", free_pages(), total_pages()), FBUFF);
        }
    }

    fbuff_print_line("");
}

void *malloc(int n) {
    if (n == 0) {
        return NULL;
    }

    int L = 0, R = 0;
    while (L < TOTAL_PAGES) {
        if (get_page(L) == PAGE_USED) {
            L++;
            R++;
            continue;
        }

        while (R < TOTAL_PAGES && get_page(R) == PAGE_FREE) {
            R++;
            if ((R-L) * PAGE_SIZE >= n) break;
        }

        if ((R-L) * PAGE_SIZE >= n) {
            for (int i = L; i < R; i++) upd_page(i, PAGE_USED);
            return page_to_ptr(L);
        }

        L = R;
    }

    return NULL;
}

void *free(void *ptr, int n) {
    if (!is_valid_page(ptr)) return NULL;

    int page = ptr_to_page((char*)ptr);

    while (n > 0) {
        n -= PAGE_SIZE;

        if (page >= TOTAL_PAGES || get_page(page) == PAGE_FREE) {
            return NULL;
        }

        upd_page(page, PAGE_FREE);
        page++;
    }
    return ptr;
}

int free_pages() {
    return fpages;
}

int total_pages() {
    return TOTAL_PAGES;
}