#include "../kernel/io.h"
#include "fbuff.h"
#include "../clib/strings.h"

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

char *fb = (char*)0xb8000;
int cursor_r = 0, cursor_c = 0;
int fgclr = FBUFF_LIGHT_GREY, bgclr = FBUFF_BLACK;

void fbuff_set_char(int i, char c) {
    fb[2*i] = c;
    fb[2*i+1] = ((bgclr & 0x0F) << 4) | (fgclr & 0x0F);
}


// moves content of the buffer UP
void fbuff_scroll() {
    for (int r = 0; r < FBUFF_HEIGHT - 1; r++) {
        memcpy(fb+2*r*FBUFF_WIDTH, fb+2*(r+1)*FBUFF_WIDTH, FBUFF_WIDTH*2);
        /*for (int c = 0; c < FBUFF_WIDTH; c++) {
            fb[2*(r*FBUFF_WIDTH+c)] = fb[2*((r+1)*FBUFF_WIDTH+c)];
            fb[2*(r*FBUFF_WIDTH+c)+1] = fb[2*((r+1)*FBUFF_WIDTH+c)+1];
        }*/
    }

    int r = FBUFF_HEIGHT - 1;
    for (int c = 0; c < FBUFF_WIDTH; c++) {
        fb[2*(r*FBUFF_WIDTH+c)] = ' ';
        fb[2*(r*FBUFF_WIDTH+c)+1] = (FBUFF_BLACK << 4) | FBUFF_WHITE;
    }
}

// public functions

void fbuff_clear() {
    for (int r = 0; r < FBUFF_HEIGHT; r++) {
        for (int c = 0; c < FBUFF_WIDTH; c++) {
            fb[2*(r*FBUFF_WIDTH+c)] = ' ';
            fb[2*(r*FBUFF_WIDTH+c)+1] = (FBUFF_BLACK << 4) | FBUFF_WHITE;
        }
    }
}
int fbuff_cursor_r() {
    return cursor_r;
}
int fbuff_cursor_c() {
    return cursor_c;
}
void fbuff_advance_cursor(int n) {
    while (n-- > 0) {
        cursor_c++;
        if (cursor_c == FBUFF_WIDTH) {
            cursor_c = 0;
            cursor_r++;
        }

        if (cursor_r == FBUFF_HEIGHT) {
            cursor_r--;
            fbuff_scroll();
        }
    }
    fbuff_move_cursor_to(cursor_r, cursor_c);
}

void fbuff_move_cursor_to(int r, int c) {
    if (0 <= r && r < FBUFF_HEIGHT) {
        if (0 <= c && c <= FBUFF_WIDTH) {
            int pos = r * FBUFF_WIDTH + c;
            outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
            outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
            outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
            outb(FB_DATA_PORT,    pos & 0x00FF);

            cursor_r = r;
            cursor_c = c;
        }
    }
}

void fbuff_set_fg_color(int clr) {
    fgclr = clr;
}
int fbuff_fg_color() {
    return fgclr;
}
void fbuff_set_bg_color(int clr) {
    bgclr = clr;
}
int fbuff_bg_color() {
    return bgclr;
}

void fbuff_print_char(char s) {
    if (s == '\n') {
        if (cursor_r == FBUFF_HEIGHT - 1) {
            fbuff_scroll();
            fbuff_move_cursor_to(cursor_r, 0);
        } else {
            fbuff_move_cursor_to(cursor_r + 1, 0);
        }
        return;
    }
    fbuff_set_char(cursor_r * FBUFF_WIDTH + cursor_c, s);
    fbuff_advance_cursor(1);
}
void fbuff_print_string(char *s) {
    while (*s != 0) {
        fbuff_print_char(*s);
        s++;
    }
}
void fbuff_print_line(char *s) {
    fbuff_print_string(s);

    if (cursor_r == FBUFF_HEIGHT - 1) {
        fbuff_scroll();
        fbuff_move_cursor_to(cursor_r, 0);
    } else {
        fbuff_move_cursor_to(cursor_r + 1, 0);
    }
}