#!/bin/bash

dd if=/dev/zero of=os.img bs=512 count=26

# boot
nasm boot.asm -o boot.bin
dd if=boot.bin of=os.img bs=512 count=1 conv=notrunc

# kernel
nasm -f elf kernel.asm -o akernel.o
gcc -ffreestanding -c kernel.c -o ckernel.o -nostdlib #-m32
ld -s akernel.o ckernel.o -o kernel.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=kernel.bin of=os.img bs=512 count=17 seek=1 conv=notrunc

# test
nasm -f elf test.asm -o atest.o
gcc -ffreestanding -c test.c -o ctest.o -nostdlib #-m32
ld -s atest.o ctest.o -o test.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=test.bin of=os.img bs=512 count=4 seek=18 conv=notrunc

# loadingBar
nasm -f elf loadingBar.asm -o aloadingBar.o
gcc -ffreestanding -c loadingBar.c -o cloadingBar.o -nostdlib #-m32
ld -s aloadingBar.o cloadingBar.o -o loadingBar.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=loadingBar.bin of=os.img bs=512 count=4 seek=22 conv=notrunc

# disasm
ndisasm -b 16 os.img > log

# clean up
rm *.bin *.o
