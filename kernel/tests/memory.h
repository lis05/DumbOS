#include "../logs.h"
#include "../../clib/sformat.h"
#include "../memory.h"

int test_memory() {
    log_info(sprintf("Testing memory\n"), BOTH);
    log_info(sprintf("%i / %i\n", total_pages() - free_pages(), total_pages()), BOTH);

    void *ptr = malloc(1024);
    if (ptr == NULL) log_critical("Couldn't allocate memory.\n", BOTH);
    log_info(sprintf("Allocated 1024 bytes. %p, %i / %i\n", ptr, total_pages() - free_pages(), total_pages()), BOTH);

    void *ptr2 = malloc(1000000);
    if (ptr2 == NULL) log_critical("Couldn't allocate memory.\n", BOTH); 
    log_info(sprintf("Allocated 1000000 bytes. %p, %i / %i\n", ptr2, total_pages() - free_pages(), total_pages()), BOTH);

    ptr = free(ptr, 1024);
    if (ptr == NULL) log_critical("Couldn't free memory.\n", BOTH);
    log_info(sprintf("Freed 1024 bytes. %p, %i / %i\n", ptr, total_pages() - free_pages(), total_pages()), BOTH);


    ptr = malloc(512);
    if (ptr == NULL) log_critical("Couldn't allocate memory.\n", BOTH);
    log_info(sprintf("Allocated 512 bytes. %p, %i / %i\n", ptr, total_pages() - free_pages(), total_pages()), BOTH);

    void *ptr3 = malloc(512);
    if (ptr == NULL) log_critical("Couldn't allocate memory.\n", BOTH);
    log_info(sprintf("Allocated 512 bytes. %p, %i / %i\n", ptr3, total_pages() - free_pages(), total_pages()), BOTH);

    ptr = free(ptr, 512);
    if (ptr == NULL) log_critical("Couldn't free memory.\n", BOTH);
    log_info(sprintf("Freed 512 bytes. %p, %i / %i\n", ptr, total_pages() - free_pages(), total_pages()), BOTH);

    ptr = free(ptr3, 512);
    if (ptr == NULL) log_critical("Couldn't free memory.\n", BOTH);
    log_info(sprintf("Freed 512 bytes. %p, %i / %i\n", ptr, total_pages() - free_pages(), total_pages()), BOTH);

    
    ptr = malloc(15000);
    if (ptr == NULL) log_critical("Couldn't allocate memory.\n", BOTH);
    log_info(sprintf("Allocated 15000 bytes. %p, %i / %i\n", ptr, total_pages() - free_pages(), total_pages()), BOTH);


    ptr = free(ptr, 15000);
    if (ptr == NULL) log_critical("Couldn't free memory.\n", BOTH);
    log_info(sprintf("Freed 15000 bytes. %p, %i / %i\n", ptr, total_pages() - free_pages(), total_pages()), BOTH);

    ptr = free(ptr2, 1000000);
    if (ptr == NULL) log_critical("Couldn't free memory.\n", BOTH);
    log_info(sprintf("Freed 1000000 bytes. %p, %i / %i\n", ptr, total_pages() - free_pages(), total_pages()), BOTH);

    return 0;
}