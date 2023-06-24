#include "isr.h"
#include "logs.h"
#include "../clib/sformat.h"

void isr_handler(registers_t regs)
{
   log_info(sprintf("received interrupt: %i", regs.int_no), BOTH);
} 