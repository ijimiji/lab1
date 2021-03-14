all: run

asm:
	nasm -f elf64 triangle.asm 
	nasm -f elf64 dot.asm 
c: asm
	gcc main.c dot.o triangle.o -o main
run: c
	./main