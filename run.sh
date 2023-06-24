#!/bin/bash

# ASM part
ASM=nasm
ASMFLAGS='-f elf'

# C part
CC=gcc
CFLAGS='-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c'

# LD part
LDFLAGS='-T link.ld -melf_i386'
LDOBJECTS='bin/loader.o bin/kmain.o bin/ioa.o bin/ioc.o bin/fbuff.o bin/serial.o bin/strings.o bin/logs.o bin/conv.o'

# building ASM
$ASM $ASMFLAGS "boot/loader.s" -o "bin/loader.o"
$ASM $ASMFLAGS "kernel/io.s" -o "bin/ioa.o"

# building C
$CC $CFLAGS "kernel/kmain.c" -o "bin/kmain.o"
$CC $CFLAGS "kernel/io.c" -o "bin/ioc.o"
$CC $CFLAGS "kernel/logs.c" -o "bin/logs.o"
$CC $CFLAGS "drivers/fbuff.c" -o "bin/fbuff.o"
$CC $CFLAGS "drivers/serial.c" -o "bin/serial.o"
$CC $CFLAGS "clib/strings.c" -o "bin/strings.o"
$CC $CFLAGS "clib/conv.c" -o "bin/conv.o"

# linking kernel
ld $LDFLAGS $LDOBJECTS -o bin/kernel.elf

# generating os image
cp bin/kernel.elf iso/boot/kernel.elf
genisoimage -R                              \
            -b boot/grub/stage2_eltorito    \
            -no-emul-boot                   \
            -boot-load-size 4               \
            -A os                           \
            -input-charset utf8             \
            -quiet                          \
            -boot-info-table                \
            -o bin/os.iso                   \
            iso
        
bochs -q

