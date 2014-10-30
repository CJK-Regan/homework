#!/bin/bash
dd if=/dev/zero of=os.img bs=512 count=4
nasm loader.asm -o loader.bin
nasm hello.asm -o hello.bin
nasm count.asm -o count.bin
nasm ball.asm -o ball.bin
dd if=loader.bin of=os.img bs=512 count=1 conv=notrunc
dd if=hello.bin of=os.img bs=512 count=1 seek=1 conv=notrunc
dd if=count.bin of=os.img bs=512 count=1 seek=2 conv=notrunc
dd if=ball.bin of=os.img bs=512 count=1 seek=3 conv=notrunc
