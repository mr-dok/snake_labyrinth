CC = gcc
CFLAGS = -std=c99 -pedantic-errors -Wall -Wextra -O2 -Wno-unused-result -g -DDEBUG

.PHONY: snake
snake: snake.o main.o
	$(CC) $(CFLAGS) bin/snake.o bin/main.o -o bin/snake

.PHONY: main.o
main.o: main.c snake.h
	$(CC) $(CFLAGS) -c main.c -o bin/main.o

.PHONY: snake.o
snake.o: snake.c snake.h create_dir
	$(CC) $(CFLAGS) -c snake.c -o bin/snake.o

.PHONY: create_dir
create_dir:
ifeq ($(wildcard bin),)
	mkdir -p bin
endif

.PHONY: valgrind
valgrind: snake
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt bin/snake

.PHONY: documentation
documentation:
	/opt/doxygen doxygen_config

.PHONY: clean
clean:
	$(RM) bin/*
	find . -name "*.txt" ! -name "CMakeLists.txt" -type f -delete
	$(RM) massif.out.*
