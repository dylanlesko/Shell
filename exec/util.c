#include <stdio.h>
#include "list.h"

void prepForExec(char *Args[],LL *node) {
	
	Args[0] = node->command;
	
	int i;
	i = 0;
	while((strcmp(node->args[i],"")) != 0) {
		Args[i+1] = node->args[i];
		i++;
	}

	Args[i+1] = NULL;

	return;

}
