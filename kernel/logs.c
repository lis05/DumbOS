#include "../clib/strings.h"
#include "../drivers/fbuff.h"
#include "../drivers/serial.h"

#include "logs.h"

void kpanic() {
    char *message = "Kernel panic has occured. The system has to stop.";
    int len = strlen(message);

    log_info("\n", BOTH);
    log_info(message, SERIAL);


    fbuff_set_bg_color(FBUFF_RED);
    for (int c = 0; c < FBUFF_WIDTH; c++) {
        fbuff_print_char(' ');
    }
    int pad = (FBUFF_WIDTH - len) / 2;
    for (int c = 0; c < pad; c++) {
        fbuff_print_char(' ');
    }
    fbuff_set_fg_color(FBUFF_WHITE);
    fbuff_print_string(message);
    for (int c = 0; c < FBUFF_WIDTH - len - pad; c++) {
        fbuff_print_char(' ');
    }
    for (int c = 0; c < FBUFF_WIDTH; c++) {
        fbuff_print_char(' ');
    }

    while(1){}

}

void log(char *msg, int level, int dev) {
    switch (level) {
    case INFO:
        if (dev == SERIAL) {
            serial_write_string(COM1, "[INFO] ");
            serial_write_string(COM1, msg);
        } else if (dev == FBUFF) {
            int old = fbuff_fg_color();

            fbuff_set_fg_color(FBUFF_WHITE);
            fbuff_print_string("*   ");
            fbuff_print_string(msg);
            fbuff_set_fg_color(old);
        } else {
            log(msg, level, SERIAL);
            log(msg, level, FBUFF);
        }
        break;
    case DEBUG:
        if (dev == SERIAL) {
            serial_write_string(COM1, "[DEBUG] ");
            serial_write_string(COM1, msg);
        } else if (dev == FBUFF) {
            int old = fbuff_fg_color();

            fbuff_set_fg_color(FBUFF_LIGHT_GREY);
            fbuff_print_string("*   ");
            fbuff_print_string(msg);
            fbuff_set_fg_color(old);
        } else {
            log(msg, level, SERIAL);
            log(msg, level, FBUFF);
        }
        break;
    case ERROR:
        if (dev == SERIAL) {
            serial_write_string(COM1, "[ERROR] ");
            serial_write_string(COM1, msg);
        } else if (dev == FBUFF) {
            int old = fbuff_fg_color();

            fbuff_set_fg_color(FBUFF_LIGHT_RED);
            fbuff_print_string("*   ");
            fbuff_print_string(msg);
            fbuff_set_fg_color(old);
        } else {
            log(msg, level, SERIAL);
            log(msg, level, FBUFF);
        }
        break;
    case CRITICAL:
        if (dev == SERIAL) {
            serial_write_string(COM1, "[CRITICAL] ");
            serial_write_string(COM1, msg);
        } else if (dev == FBUFF) {
            int old = fbuff_fg_color();

            fbuff_set_fg_color(FBUFF_RED);
            fbuff_print_string("*   ");
            fbuff_print_string(msg);
            fbuff_set_fg_color(old);
            kpanic();
        } else {
            log(msg, level, SERIAL);
            log(msg, level, FBUFF);
            kpanic();
        }
        break;
    }

}

void log_info(char *msg, int dev) {
    log(msg, INFO, dev);
}
void log_debug(char *msg, int dev) {
    log(msg, DEBUG, dev);
}
void log_error(char *msg, int dev) {
    log(msg, ERROR, dev);
}
void log_critical(char *msg, int dev) {
    log(msg, CRITICAL, dev);
}