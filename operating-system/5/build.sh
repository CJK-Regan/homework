#!/bin/bash

dd if=/dev/zero of=os.img bs=512 count=26

# boot
nasm boot.asm -o boot.bin
dd if=boot.bin of=os.img bs=512 count=1 conv=notrunc

# kernel
nasm -f elf kernel.asm -o akernel.o
gcc -ffreestanding -c kernel.c -o ckernel.o -nostdlib #-m32
nasm -f elf sysInt.asm -o sysInt.o
ld -s akernel.o ckernel.o sysInt.o -o kernel.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=kernel.bin of=os.img bs=512 count=20 seek=1 conv=notrunc

# asc
nasm -f elf asc.asm -o aasc.o
gcc -ffreestanding -c asc.c -o casc.o -nostdlib #-m32
ld -s aasc.o casc.o -o asc.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=asc.bin of=os.img bs=512 count=2 seek=21 conv=notrunc

# test5
nasm -f elf test5.asm -o atest5.o
gcc -ffreestanding -c test5.c -o ctest5.o -nostdlib #-m32
ld -s atest5.o ctest5.o -o test5.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=test5.bin of=os.img bs=512 count=3 seek=23 conv=notrunc

# clean up
rm *.bin *.o
