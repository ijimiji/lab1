all: run

asm:
	nasm -f elf64  f.asm
c: asm
	gcc  -no-pie main.c f.o -o main
run: c
	./main