CC = gcc
CFLAGS = -g
HFILES = defs.h types.h list.h util.h
SHELLFILES = shell.c tok.c list.c isstdio.c util.c
TESTFILES = tests.c

all: shell

shell: $(SHELLFILES)
	$(CC) $(CFLAGS) -o shell $(SHELLFILES)
	
test: shell
	$(CC) $(CFLAGS) -o shelltester $(TESTFILES)

clean:
	rm -rf *.o;
