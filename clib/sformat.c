#include "sformat.h"
#include "strings.h"
#include "vargs.h"

char *u_to_s(unsigned int x, char *out) {
    if (x == 0) {
        out[0] = '0';
        out[1] = 0;
        return out+1;
    }

    int ptr = 0;
    while (x > 0) {
        out[ptr] = '0' + (x % 10);
        x /= 10;
        ptr++;
    }
    for (int i = 0; i < ptr/2; i++) {
        int t = out[i];
        out[i] = out[ptr - i - 1];
        out[ptr - i - 1] = t;
    }
    out[ptr] = 0;
    return out+ptr;
}

char *i_to_s(int x, char *out) {
    if (x >= 0) return u_to_s(x, out);
    
    *out = '-';
    out++;
    x *= -1;
    return u_to_s(x, out);
}

char *p_to_s(void *x, char *out) {
    static char *c = "0123456789ABCDEF";
    
    unsigned int addr = (unsigned int)x;

    *out = '0'; out++;
    *out = 'x'; out++;

    for (int i = 0; i < 8; i++) {
        out[7-i] = c[addr % 16];
        addr /= 16;
    }
    
    out[8] = 0;
    return out+8;
}


#define BUFF_SIZE 32*(1<<10) // 32 kb
char buff[BUFF_SIZE];

// format things start with %
// currently few things are supported:
// %u - gets replaced by a 32bit unsigned number
// %i - gets replaced by a 32bit signed number
// %p - gets replaced by a 32bit pointer address
// %c - gets replaced by a char
// %s - gets replaced by a string
// anything else is considered as a text, so it's copied to dst
char *sprintf(char*fmt, ...) {
    char *dst = buff;
    va_list args;
    va_start(args, fmt);

    while (*fmt != 0) {
        if (*fmt != '%') {
            *dst = *fmt;
            dst++;
            fmt++;
            continue;
        }

        fmt++;
        if (*fmt == 'u') {
            unsigned int i = va_arg(args, unsigned int);
            dst = u_to_s(i, dst);
        } else if (*fmt == 'i') {
            int i = va_arg(args, int);
            dst = i_to_s(i, dst);
        } else if (*fmt == 'p') {
            void *i = va_arg(args, void*);
            dst = p_to_s(i, dst);
        } else if (*fmt == 'c') {
            int i = va_arg(args, int);
            *dst = (char)i;
            dst++;
        } else if (*fmt == 's') {
            char* i = va_arg(args, char*);
            dst = memcpy(dst, i, strlen(i));
        }

        fmt++;
    }
    *dst = 0;

    return buff;
}