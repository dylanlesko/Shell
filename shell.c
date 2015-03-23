#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "defs.h"
#include "types.h"
#include "list.h"

boolean show_prompt = true;
char dir_home[ MEM_MAX ];
char dir_cur[ MEM_MAX ];
char prompt[ 2 ];


void shell_exit(void)
{
	printf("\n");
}





/* */
boolean firstRun;

int main(){
	firstRun = true;	

	atexit(shell_exit);
	//LList **argsLL = ( LList** )malloc( sizeof( LList ) );

	if ( (shell_init( ) ) == 0 )
	{
		shell_prompt();
	}
	exit( 0 );
}



/* */


int shell_init(){

	if( is_std_i() == true || firstRun == true){
		firstRun = false;

		show_prompt = true;
		strcpy( prompt, "$: " );
		strcpy( dir_home, getenv( "HOME" ) );
		getcwd( dir_cur, MEM_MAX );

/*
		char wdir[1024];
		getcwd(wdir, sizeof(wdir));
		strcpy(dir_home, wdir);
*/

		return 0;
	}else{
		printf("stdin is not a terminal\n");
		return 1;
	}
	return 1;
}



/* */

int shell_prompt()
{	
	while( show_prompt == true )
	{
		getcwd( dir_cur, MEM_MAX );

		fputs( RESET_FORMAT, stdout );
		fputs( dir_cur, stdout );
		fputs( MAKE_RED, stdout );
		fputs( prompt, stdout );
		fputs( RESET_FORMAT, stdout );

		LL *head; head = NULL;

		if( ( shell_cmd_in(&head) ) == 0 )
			continue;
		else
			return 1;
	}
	return 0;
}

int alphaCheck(char *cmd_line) {
	
	int i,alNumFlag; alNumFlag = 0; // 1 means there are alnums, 0 means no alnums
	for(i = 0; i < strlen(cmd_line); i++) {
		if(isalnum(cmd_line[i]))
			alNumFlag = 1;
	}

	return alNumFlag;
}

/* */


int shell_cmd_in(LL **head)
{
	char cmd_line[ MEM_MAX ];
	memset( cmd_line, 0, MEM_MAX );

	if ( fgets( cmd_line, MEM_MAX, stdin ) == NULL ){
		return 1;
	}



	/* Replacing trailing newline with a terminating nullchar */
	size_t ln = strlen(cmd_line) - 1;
	if ( cmd_line[ln] == '\n' )
		cmd_line[ln] = '\0';

	// if the entire string doesn't have any alpha numerics, then just print another prompt

	
	int alphaNumFlag;
	alphaNumFlag = alphaCheck(cmd_line);
		
	if(alphaNumFlag == 1) {	
	
		//shell_tok( cmd_line, list );
	
		newTok(cmd_line,head); // head should now have a list of commands
		execute(*head);
		//destroy(*head);
	} else if(alphaNumFlag == 0) {
		printf("");
	}




	return 0;
}


