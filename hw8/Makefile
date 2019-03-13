# Ishan's Makefile
# yeet

CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -Wextra -Werror -O2 -Wstrict-prototypes -Wold-style-definition -g
OBJECTS = todo.o todo_data.o todo_helpers.o

todo: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o todo
$(OBJECTS): todo.h
todo.o: useful_strings.h