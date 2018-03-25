CC = gcc
INC = -Iinclude
OBJDIR = obj
SRCDIR = src
HEADER = include
CC_FLAGS = -w -pedantic -g $(INC) -lncurses

EXEC = Vim++
SOURCES = $(shell find $(SRCDIR) -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CC_FLAGS) -o $(EXEC)
	
$(OBJDIR)/proj2.o: $(SRCDIR)/proj2.c | make-folder
	$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)/%.h| make-folder
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(EXEC) $(OBJDIR)

make-folder:
	mkdir -p $(OBJDIR)
