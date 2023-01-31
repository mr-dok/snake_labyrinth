all: main.c 
	gcc -Wall -pedantic -std=c99 -o bin/main main.c -lncurses