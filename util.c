#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "util.h"
#include "defs.h"

extern char dir_home[MEM_MAX];


int our_exit(char args[50][2048]){
	if(args==NULL){
		exit(0);
	}

	exit(atoi(args[0]));
}

int our_cd(char dir[50][2048]){

	char Null[2048];
	memset(Null,'\0',2048);
	if(strcmp(dir[0],Null) == 0){
		chdir(dir_home);	
		return 0;
	}

	if(strlen(dir[1]) >0){
		fprintf(stderr, "\ncd: too many arguments\n");
		return 0;
	}
	
	char null[1024];
	memset(null,0,1024);

	char cwd[1024];
	if(strncmp(dir[0],"/", 1) != 0){
		if (getcwd(cwd, sizeof(cwd)) != 0){
			//fprintf(stdout, "Current working dir: %s\n", cwd);

			char path[2048];
			strcpy(path, cwd);
			strcat(path, "/");
			strcat(path, dir[0]);
			chdir(path);

		}else{
			perror("getcwd() error");
		}
	}else{
		chdir(dir[0]);
	}

	
	char cwd2[1024];
	getcwd(cwd2, sizeof(cwd2));
	printf("now in dir %s\n",cwd2);

}

int builtIn(LL *cmd) {
	if(strcmp(cmd->command,"cd") == 0){
		our_cd(cmd->args);
		return 1;
	}else if (strcmp(cmd->command,"exit") == 0){
		our_exit(cmd->args);
		return 1;
	}else{
		return 0;
	}
}


void prepForExec(char *Args[],LL *node) {
	
	Args[0] = node->command;

	char null[2048];
	memset(null,'\0',2048);

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

int builtInCheck(LL *cmd) {

	if(strcmp(cmd->command,"cd") == 0)
		return 1;
	else if(strcmp(cmd->command,"exit") == 0)
		return 1;
	else
		return 0;
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
					if(builtInCheck(cmd)) {
						//printf("built-in %s: do nothing\n",cmd->command);
						exit(0);
					} else {
						dup2(pipes[i][1],1);
                                        	closeFDsingle(pipes[i][1],pipes,pipeNum);
	                                        char *Args[51];
	                                        prepForExec(Args,cmd);
	                                        execvp(Args[0],Args);
	                                        perror(Args[0]);
					}
                                } else if(i == pipeNum) { // end
					if(builtInCheck(cmd)) {
						//printf("built-in %s: do nothing\n",cmd->command);
						//builtIn(cmd);
						exit(0);
					} else {
						dup2(pipes[i-1][0],0);
	                                        closeFDsingle(pipes[i-1][0],pipes,pipeNum);
	                                        char *Args[51];
	                                        prepForExec(Args,cmd);
	                                        execvp(Args[0],Args);
        	                                perror(Args[0]);
					}
                                } else { // middle
					if(builtInCheck(cmd)) {
						//printf("built-in %s: do nothing\n",cmd->command);
						//builtIn(cmd);
						exit(0);
					} else {
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
				if(builtInCheck(cmd)) {
					//printf("Built-in called from parent\n");
					builtIn(cmd);
				}
			
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




