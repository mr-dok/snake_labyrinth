CC = gcc
CFLAGS_sanitizer = -std=c99 -pedantic-errors -Wall -Wextra -O0 -Wno-unused-result -fsanitize=address -fno-omit-frame-pointer -g -DDEBUG
CFLAGS_no_sanitizer = -std=c99 -pedantic-errors -Wall -Wextra -O0 -Wno-unused-result -g

.PHONY: snake
snake: snake.o main.o
	$(CC) $(CFLAGS_no_sanitizer) bin/snake.o bin/main.o -o bin/snake

.PHONY: main.o
main.o: main.c snake.h
	$(CC) $(CFLAGS_no_sanitizer) -c main.c -o bin/main.o

.PHONY: snake.o
snake.o: snake.c snake.h create_dir
	$(CC) $(CFLAGS_no_sanitizer) -c snake.c -o bin/snake.o

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
	brave-browser html/index.html

.PHONY: clean
clean:
	$(RM) bin/*
