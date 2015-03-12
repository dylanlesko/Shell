#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
#include "types.h"

int showprompt = true;

int main()
{
	LList **argsLL = (LList**)malloc(sizeof(LList));
	//shell_tok( "hi", argsLL);
	fakeShell();
	
	

	
	
}

int fakeShell()
{
	char fakeDir[2048];
	char homedir[2048];
	char cmdArgs[2048];
	
	LList **argsLL = (LList**)malloc(sizeof(LList));
	
	char prompt[2] = "$ ";
	strcpy(homedir, getenv("HOME"));
	strcpy(fakeDir, homedir);
	
	while( showprompt )
	{
		fputs(fakeDir, stdout);
		fputs(prompt, stdout);
		fgets(cmdArgs, sizeof(cmdArgs), stdin);
		
		shell_tok( cmdArgs, argsLL );
		//processSTDIO( cmdArgs,  argsLL);
		//dumpArgs( *argsLL );
		//free the argsLL here
	}
}

int processSTDIO( char* args, LList **root )
{
	//fragment args based off of quotations?
	
	char *tempToken;
	tempToken = strtok(args, "| \'\"");	
	while(tempToken != NULL)
	{
	//	insertArg( tempToken, root );
		printf("token: %s\n", tempToken);
		tempToken = strtok(NULL, "| \'\"");
	}
}


