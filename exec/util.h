#include <stdio.h>
#include "list.h"

void prepForExec(char *Args[], LL *node);
void closeFDsingle(int fd, int pipes[][2], int pipeNum);
void closeFDdouble(int one, int two, int pipes[][2],int pipeNum);
void execute(LL *head);
int builtIn(LL *cmd);
