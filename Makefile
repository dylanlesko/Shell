CC = gcc
CFLAGS = -g
HFILES = defs.h types.h
SHELLFILES = shell.c tok.c list.c

all: shell

shell: $(SHELLFILES)
	$(CC) $(CFLAGS) -o shell $(SHELLFILES)
	
clean:
	rm -rf *.o;
