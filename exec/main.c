#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

int main() {

	LL *first = (LL *)malloc(sizeof(LL));
	LL *second = (LL *)malloc(sizeof(LL));
	LL *third = (LL *)malloc(sizeof(LL));
	LL *fourth = (LL *)malloc(sizeof(LL));
	LL *fifth = (LL *)malloc(sizeof(LL));

	strcpy(first->command,"ls");
	strcpy(first->args[0],"/home/nikhil/Documents");
	first->next = second;


	strcpy(second->command,"ls");
	strcpy(second->args[0],"/home/nikhil/Downloads");
	second->next = third;
	
	strcpy(third->command,"ls");
	strcpy(third->args[0],"/home/nikhil/Desktop");
	third->next = fourth;

	strcpy(fourth->command,"ls");
	strcpy(fourth->args[0],"/home/nikhil/Pictures");
	fourth->next = fifth;

	strcpy(fifth->command,"ls");
	strcpy(fifth->args[0],"/home/nikhil/Public");
	fifth->next = NULL;

	pid_t childPid;
	int status;

	int commandNum;
	commandNum = length(first);
	pid_t pids[commandNum]; // holds the pids for all programs in the list
	int i;
	i = 0;

	LL *head;
	head = first;

	while(head != NULL) {

		if((childPid = fork()) == 0) {
			char *Args[51];
			prepForExec(Args,head);
	
			execvp(Args[0],Args);
		} else {
			pids[i] = childPid;
			i++;
			head = head->next;
		}
	}

	int j;
	for(j = 0; j < commandNum; j++) 	
		waitpid(pids[j],&status,0);

	destroy(first);

	return 0;
}

