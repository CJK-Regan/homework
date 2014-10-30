#!/bin/bash

dd if=/dev/zero of=os.img bs=512 count=15

# boot
nasm boot.asm -o boot.bin
dd if=boot.bin of=os.img bs=512 count=1 conv=notrunc

# kernel
nasm -f elf kernel.asm -o akernel.o
gcc -ffreestanding -c kernel.c -o ckernel.o -nostdlib #-m32
ld -s akernel.o ckernel.o -o kernel.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=kernel.bin of=os.img bs=512 count=10 seek=1 conv=notrunc

# counter
nasm -f elf counter.asm -o acounter.o
gcc -ffreestanding -c counter.c -o ccounter.o -nostdlib #-m32
ld -s acounter.o ccounter.o -o counter.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=counter.bin of=os.img bs=512 count=2 seek=11 conv=notrunc

# loadingBar
nasm -f elf loadingBar.asm -o aloadingBar.o
gcc -ffreestanding -c loadingBar.c -o cloadingBar.o -nostdlib #-m32
ld -s aloadingBar.o cloadingBar.o -o loadingBar.bin -Ttext 0x0 --oformat binary #-m elf_i386
dd if=loadingBar.bin of=os.img bs=512 count=2 seek=13 conv=notrunc

# clean up
rm *.bin *.o
