#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

int main() {

	LL *first = (LL *)malloc(sizeof(LL));
	LL *second = (LL *)malloc(sizeof(LL));

	strcpy(first->command,"ls");
	strcpy(first->args[0],"/home/nikhil/Documents");
	first->next = second;


	strcpy(second->command,"grep");
	strcpy(second->args[0],"Win");
	second->next = NULL;
	
	
	pid_t childPid;
	int status;

	int commandNum;
	commandNum = length(first);
	pid_t pids[commandNum]; // holds the pids for all programs in the list
	int i;
	i = 0;

	LL *progOne, *progTwo;
	progOne = first;

	int fd[2]; // file descriptors for redirection
	pipe(fd); // create the pipe between the two file descriptors

	while(progOne != NULL) {


		if(progTwo != NULL) {
			int fd[2]; // file descriptors for redirection
			pipe(fd); // create the pipe between the two file descriptors

			runsource(fd,progOne);
			rundest(fd,progTwo);
			close(fd[0]);
			close(fd[1]);
		}
	


		/*
		if((childPid = fork()) == 0) {
			char *Args[51];
			prepForExec(Args,progOne);
	
			execvp(Args[0],Args);
		} else {
			pids[i] = childPid;
			i++;
			progOne = progOne->next;
		}
		*/
	}

	while((pid = wait(&status)) != -1)
		fprintf(stderr,"Process %d exits with %d\n",pid,WEXITSTATUS(status));

	int j;
	for(j = 0; j < commandNum; j++) {	
		waitpid(pids[j],&status,0);
		printf("process %d exits with status %d\n",pids[j],status);
	}

	destroy(first);

	return 0;
}

