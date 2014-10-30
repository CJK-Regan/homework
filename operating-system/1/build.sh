#!/bin/bash
nasm ball.asm -o ball.bin
dd if=ball.bin of=ball.img bs=512 count=1
