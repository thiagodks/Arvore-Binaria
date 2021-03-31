all:	main

main:	main.o	arvore.o	io.o
	gcc	main.o	arvore.o	io.o	-o	main

main.o:	main.c	arvore.c	io.c
	gcc	-c	-Wall	io.c
	gcc	-c	-Wall	arvore.c
	gcc	-c	-std=c11	-Wall	-ggdb3	main.c
	
clean:
	rm main.o	arvore.o	io.o	main