#ifndef CLIB_STRINGS_H
#define CLIB_STRINGS_H

void* memset(void *dst, char data, int n);
void* memcpy(void *dst, void *src, int n);
int memcmp(void *a, void *b);
int strlen(char *s);

#endif