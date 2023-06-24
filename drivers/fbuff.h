#ifndef DRIVERS_FBUFF_H
#define DRIVERS_FBUFF_H

// framebuffer dimensions
#define FBUFF_WIDTH 80
#define FBUFF_HEIGHT 25

#define FBUFF_BLACK 0
#define FBUFF_BLUE 1
#define FBUFF_GREEN 2
#define FBUFF_CYAN 3
#define FBUFF_RED 4
#define FBUFF_MAGENTA 5
#define FBUFF_BROWN 6
#define FBUFF_LIGHT_GREY 7
#define FBUFF_DARK_GREY 8
#define FBUFF_LIGHT_BLUE 9
#define FBUFF_LIGHT_GREEN 10
#define FBUFF_LIGHT_CYAN 11
#define FBUFF_LIGHT_RED 12
#define FBUFF_LIGHT_MAGENTA 13
#define FBUFF_LIGHT_BROWN 14
#define FBUFF_WHITE 15

void fbuff_clear();
int fbuff_cursor_r();
int fbuff_cursor_c();
void fbuff_advance_cursor(int n);
void fbuff_move_cursor_to(int r, int c);

void fbuff_set_fg_color(int clr);
int fbuff_fg_color();
void fbuff_set_bg_color(int clr);
int fbuff_bg_color();

void fbuff_print_char(char s);
void fbuff_print_string(char *s);
void fbuff_print_line(char *s);

#endif