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

list: main.c util.h util.c types.h defs.h list.h list.c
	clear
	gcc -g main.c util.h util.c types.h defs.h list.h list.c -o main
	

clean:
	rm -rf *.o;
