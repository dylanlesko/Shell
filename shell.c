#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
#include "types.h"
#include "list.h"

boolean show_prompt = true;
char dir_home[ MEM_MAX ];
char dir_cur[ MEM_MAX ];
char prompt[ 2 ];





void shell_exit(void){
	printf("\n\n");
}





/* */
int main(){
	

	atexit(shell_exit);
	LL **argsLL = ( LL** )malloc( sizeof( LL ) );
	if ( (shell_init( ) ) == 0 ){
		shell_prompt( argsLL );
	}
	exit( 0 );
}



/* */


int shell_init(){

	if( is_std_i() == true ){

		show_prompt = true;
		strcpy( prompt, "$: " );
		strcpy( dir_home, getenv( "HOME" ) );
		getcwd( dir_cur, MEM_MAX );


		char wdir[1024];
		getcwd(wdir, sizeof(wdir));
		strcpy(dir_home, wdir);

		return 0;
	}else{
		printf("stdin is not a terminal\n");
		return 1;
	}
	return 1;
}



/* */

int shell_prompt( LL** list ){	

	while( show_prompt == true ){
		fputs( RESET_FORMAT, stdout );
		fputs( dir_cur, stdout );
		fputs( MAKE_RED, stdout );
		fputs( prompt, stdout );
		fputs( RESET_FORMAT, stdout );

		if( ( shell_cmd_in( list ) ) == 0 )
			continue;
		else
			return 1;
	}
	return 0;
}



/* */

int shell_cmd_in( LL** list ){

	char cmd_line[ MEM_MAX ];
	memset( cmd_line, 0, MEM_MAX );

	if ( fgets( cmd_line, MEM_MAX, stdin ) == NULL ){
		return 1;
	}



	/* Replacing trailing newline with a terminating nullchar */
	size_t ln = strlen(cmd_line) - 1;
	if ( cmd_line[ln] == '\n' )
		cmd_line[ln] = '\0';
	LL* toked;
	toked = shell_tok( cmd_line, list );
	//printList(toked);

	//shell_tok( cmd_line, list );
	newTok(cmd_line);



	execute(toked);

//	putting destroy here causes it to only work once
//	destroy(toked);
	return 0;
}
