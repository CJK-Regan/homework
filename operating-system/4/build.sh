#!/bin/bash

dd if=/dev/zero of=os.img bs=512 count=15

# boot
nasm boot.asm -o boot.bin
dd if=boot.bin of=os.img bs=512 count=1 conv=notrunc

# kernel
nasm -f elf kernel.asm -o akernel.o
gcc -ffreestanding -c kernel.c -o ckernel.o #-m32
ld -s akernel.o ckernel.o -o kernel.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=kernel.bin of=os.img bs=512 count=10 seek=1 conv=notrunc

# asc
nasm -f elf asc.asm -o aasc.o
gcc -ffreestanding -c asc.c -o casc.o #-m32
ld -s aasc.o casc.o -o asc.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=asc.bin of=os.img bs=512 count=2 seek=11 conv=notrunc

# ball
nasm ball.asm -o ball.bin
dd if=ball.bin of=os.img bs=512 count=2 seek=13 conv=notrunc

# clean up
rm *.bin *.o

# disasm
#ndisasm -b 16 os.img > log
