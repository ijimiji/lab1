all: run

asm:
	nasm -f elf64 string.asm
c: asm
	gcc main.c string.o -o main
run: c
	./main