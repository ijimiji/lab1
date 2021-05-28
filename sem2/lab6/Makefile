all: run

asm:
	nasm -f elf64  magic.asm
c: asm
	gcc -no-pie  main.c magic.o -o main
run: c
	./main
