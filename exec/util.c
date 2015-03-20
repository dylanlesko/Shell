#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


void execute(LL *head) {


	int status;
        LL *cmd;
        cmd = head;
        pid_t pid;

        // Create all the pipes first, then spawn all the children and assign the file descriptors

        int pipeNum,listLen;
        listLen = length(head);
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
					if(builtIn(cmd)) 
						printf("built-in action: %s\n",cmd->command);
					else {
						dup2(pipes[i][1],1);
                                        	closeFDsingle(pipes[i][1],pipes,pipeNum);
	                                        char *Args[51];
	                                        prepForExec(Args,cmd);
	                                        execvp(Args[0],Args);
	                                        perror(Args[0]);
					}
                                } else if(i == pipeNum) { // end
					if(builtIn(cmd))
						printf("built-in action: %s\n",cmd->command);
					else {
						dup2(pipes[i-1][0],0);
	                                        closeFDsingle(pipes[i-1][0],pipes,pipeNum);
	                                        char *Args[51];
	                                        prepForExec(Args,cmd);
	                                        execvp(Args[0],Args);
        	                                perror(Args[0]);
					}
                                } else { // middle
					if(builtIn(cmd))
						printf("built-in action: %s\n",cmd->command);
					else {
						dup2(pipes[i-1][0],0);
	                                        dup2(pipes[i][1],1);
						closeFDdouble(pipes[i-1][0],pipes[i][1],pipes,pipeNum);
	                                        char *Args[51];
	                                        prepForExec(Args,cmd);
	                                        execvp(Args[0],Args);
	                                        perror(Args[0]);
					}
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


	 while((pid = wait(&status)) != -1)
                fprintf(stderr,"Process %d exits with %d\n",pid,WEXITSTATUS(status));


}



int builtIn(LL *cmd) {

	if(strcmp(cmd->command,"cd") == 0)
		return 1;
	else if (strcmp(cmd->command,"exit") == 0)
		return 1;
	else
		return 0;
}






