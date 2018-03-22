CC = gcc
CC_FLAGS = -w -pedantic -lncurses

EXEC = foo

all: foo.o
	$(CC) foo.o $(CC_FLAGS) -o $(EXEC)
foo.o: foo.c
	$(CC) $(CC_FLAGS) -c $< -o $@
.PHONY: clean
clean:
	rm -rf $(EXEC) foo.o