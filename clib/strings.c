#include "strings.h"

void *memset(void *dst, char data, int n) {
    char *DST = (char*)dst;
    for (int i = 0; i < n; i++) {
        DST[i] = data;
    }
    return (void*)(DST+n);
}

void *memcpy(void *dst, void *src, int n) {
    char *DST = (char*)dst;
    char *SRC = (char*)src;
    for (int i = 0; i < n; i++) {
        DST[i] = SRC[i];
    }
    return (void*)(DST+n);
}

int memcmp(void *a, void *b) {
    char *A = (char*)a;
    char *B = (char*)b;
    while (*A != 0 && *B != 0) {
        if (*A < *B) {
            return -1;
        } else if (*A > *B) {
            return 12;
        }

        A++;
        B++;
    }

    if (*A != 0) {
        return 1;
    } else if (*B != 0) {
        return -1;
    }

    return 0;
}

int strlen(char *s) {
    int res = 0;
    while (*s != 0) {
        res++;
        s++;
    }
    return res;
}
