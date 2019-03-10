# Ishan's Makefile
# yeet

CFLAGS = -std=c99 -Wall -pedantic -Wextra -Werror -O2 -Wstrict-prototypes -Wold-style-definition -g
OBJECTS = todo.o todo_data.o todo_helpers.o

todo: $(OBJECTS)
	cc $(OBJECTS) $(CFLAGS) -o todo
$(OBJECTS): todo.h
todo.o: useful_strings.h