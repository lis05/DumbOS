#ifndef KERNEL_MEMORY_H
#define KERNEL_MEMORY_H

#define NULL 0x0

void init_memory();
void *malloc(int n);
void *free(void *ptr, int n);
int free_pages();
int total_pages();

#endif