CC = gcc
CFLAGS = -std=c99 -pedantic-errors -Wall -O0 -Wno-unused-result -g

.PHONY: snake
snake: snake.o main.o
	$(CC) $(CFLAGS) bin/snake.o bin/main.o -o bin/snake

.PHONY: main.o
main.o: main.c snake.h
	$(CC) $(CFLAGS) -c main.c -o bin/main.o

.PHONY: snake.o
snake.o: snake.c snake.h
	$(CC) $(CFLAGS) -c snake.c -o bin/snake.o

.PHONY: valgrind
valgrind: snake
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt bin/snake

.PHONY: clean
clean:
	$(RM) bin/*
