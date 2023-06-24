#include "io.h"
#include "logs.h"
#include "memory.h"
#include "../drivers/serial.h"
#include "../drivers/fbuff.h"
#include "../clib/sformat.h"
#include "../clib/strings.h"

#include "tests/sprintf.h"
#include "tests/memory.h"

#include "descriptor_tables.h"

void waiting_anim() {
    int cursor_r = fbuff_cursor_r();
    int cursor_c = fbuff_cursor_c();
    static int n = 0;

    int moves = 300000;

    if (n ==moves) {
        fbuff_print_line("");
        fbuff_print_string("   \n---\n   ");
    } else if (n == 2*moves) {
        fbuff_print_line("");
        fbuff_print_string("\\  \n \\ \n  \\");
    } else if (n == 3*moves) {
        fbuff_print_line("");
        fbuff_print_string(" | \n | \n | ");
    } else if (n == 4*moves) {
        fbuff_print_line("");
        fbuff_print_string("  /\n / \n/  ");
    }

    fbuff_move_cursor_to(cursor_r, cursor_c);
    n++;

    if (n > 4*moves) {
        n = 0;
    }
}

void kmain(unsigned int stack_base) {
    fbuff_clear();

    serial_configure_baud_rate(COM1, 1); // COM1
    serial_configure_line(COM1); // COM1
    serial_configure_fifo(COM1);
    serial_configure_modem(COM1);

    log_info("Booted successfully. Starting initializing and testing the system\n", BOTH);

    test_sprintf();

    log_info(sprintf("stack base: %p\n", stack_base), BOTH);

    init_memory();
    test_memory();

    log_info("Initializing GDT and IDT\n", BOTH);
    init_descriptor_tables();

    asm volatile("int $0x3");
    asm volatile("int $0x4");
    


    log_info("System seems to work fine.", BOTH);

    while(1)waiting_anim();
}