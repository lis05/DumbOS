#ifndef KERNEL_SERIAL_H
#define KERNEL_SERIAL_H

#define COM1 0x3F8

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
void serial_configure_line(unsigned short com);
void serial_configure_fifo(unsigned short com);
void serial_configure_modem(unsigned short com);
int serial_is_transmit_fifo_empty(unsigned short com);
void serial_write_char(unsigned short com, unsigned char data);
void serial_write_string(unsigned short com, char *data);

#endif