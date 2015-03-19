#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

void closeFDsingle(int fd, int pipes[][2], int pipeNum) {

	int i, j;

	for(i = 0; i < pipeNum; i++) {
		for(j = 0; j < 2; j++) {
			if(pipes[i][j] != fd)
				close(pipes[i][j]);
		}
	}
}

void closeFDdouble(int one, int two, int pipes[][2], int pipeNum) {

	int i, j;

	for(i = 0; i < pipeNum; i++) {
		for(j = 0; j < 2; j++) {
			if((pipes[i][j] != one) && (pipes[i][j] != two))
				close(pipes[i][j]);
		}
	}
}

int main() {

	LL *first = (LL *)malloc(sizeof(LL));
	LL *second = (LL *)malloc(sizeof(LL));
	LL *third = (LL *)malloc(sizeof(LL));

	strcpy(first->command,"ls");
	strcpy(first->args[0],"/home/nikhil/Downloads");
	first->next = second;


	strcpy(second->command,"grep");
	strcpy(second->args[0],"e");
	second->next = third;

		
	strcpy(third->command,"sort");
	strcpy(third->args[0],"-r");
	third->next = NULL;
	


	
	int status;
	LL *cmd;
	cmd = first;
	pid_t pid;

	// Create all the pipes first, then spawn all the children and assign the file descriptors

	int pipeNum,listLen;
	listLen = length(first);
	pipeNum = listLen - 1;
	int pipes[pipeNum][2];

	int i;
	for(i = 0; i < pipeNum; i++) 
		pipe(pipes[i]);	
	

	for(i = 0; i < listLen; i++) {

		//printf("i = %u\n",i);	
		switch(pid = fork()) {

			case 0:
				if(i == 0) { // beginning
					dup2(pipes[i][1],1);
					closeFDsingle(pipes[i][1],pipes,pipeNum);
					char *Args[51];
					prepForExec(Args,cmd);
					execvp(Args[0],Args);
					perror(Args[0]);
				} else if(i == pipeNum) { // end
					dup2(pipes[i-1][0],0);
					closeFDsingle(pipes[i-1][0],pipes,pipeNum);
					char *Args[51];
					prepForExec(Args,cmd);
					execvp(Args[0],Args);
					perror(Args[0]);
				} else { // middle
					dup2(pipes[i-1][0],0);
					dup2(pipes[i][1],1);
					closeFDdouble(pipes[i-1][0],pipes[i][1],pipes,pipeNum);
					char *Args[51];
					prepForExec(Args,cmd);
					execvp(Args[0],Args);
					perror(Args[0]);
				}
		
			default:
				if(i < pipeNum) {
					close(pipes[i][1]); //close(pipes[i][0]);
					cmd = cmd->next;
				}
				break;
	
			case -1:
				perror("fork");
				exit(1);
		}
	}






//	printf("We get out of the for loop in the parent\n");


	while((pid = wait(&status)) != -1){
		int i;
	}
		//fprintf(stderr,"Process %d exits with %d\n",pid,WEXITSTATUS(status));

	destroy(first);

	return 0;
}



