#!/usr/local/bin/python3.9

import os, glob

ASM = "nasm"
ASMFLAGS = "-f elf"

CC = "gcc"
CFLAGS = "-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c"

LDFLAGS = "-T link.ld -melf_i386"
LDOBJECTS = ""

DIRS = [
    "boot",
    "clib",
    "kernel",
    "drivers",
]

def run(cmd): 
    print(cmd)
    os.system(cmd)

for dir in DIRS:
    run(f"mkdir -p bin/{dir}")
    for file in glob.glob(f"{dir}/**", recursive=True):
        if file.endswith(".s"):
            run(f"{ASM} {ASMFLAGS} {file} -o bin/{file[:-2]}.o")
            LDOBJECTS += f"bin/{file[:-2]}.o "
        
        if file.endswith(".c"):
            run(f"{CC} {CFLAGS} {file} -o bin/{file[:-2]}.o")
            LDOBJECTS += f"bin/{file[:-2]}.o "



run(f"ld {LDFLAGS} {LDOBJECTS} -o bin/kernel.elf")

run("cp bin/kernel.elf iso/boot/kernel.elf")
run("genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os \
    -input-charset utf8 -quiet -boot-info-table -o bin/os.iso iso")
run("bochs -q")

        
