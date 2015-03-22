#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include "list.h"

void prepForExec(char *Args[], LL *node);
void closeFDsingle(int fd, int pipes[][2], int pipeNum);
void closeFDdouble(int one, int two, int pipes[][2],int pipeNum);
void execute(LL *head);

int builtIn(LL *cmd);
/*
int our_cd(char[50][2048]);
int our_exit(char[50][2048]);

struct builtins{
	char *name;
	int (*f)();
	existBuilts[2]= {
		{"cd", &our_cd},
		{"exit", &our_exit},
};

typedef struct builtin builtins;
*/
#endif
