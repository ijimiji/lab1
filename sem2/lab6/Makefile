default: all
c:
	clang++ -fasm-blocks main.cpp module.o -o main

asm:
	nasm -f macho64 module.asm

run:
	./main

all: asm c run