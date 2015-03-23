#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "defs.h"
#include "types.h"

boolean show_prompt = true;
char dir_home[ MEM_MAX ];
char dir_cur[ MEM_MAX ];
char prompt[ 2 ];

/* fluff exit function to just add a newline at program termination */
void shell_exit( void )	{
	printf( "\n" );
}

/* default function to start up a shell process */
int main()	{

	prepfs();	

	atexit( shell_exit) ;

	if ( (shell_init( ) ) == 0 )
	{
		shell_prompt();
	}
	exit( 0 );
}

/* initialize the shell variables */
int shell_init()	{
	show_prompt = is_std_i();
	strcpy( prompt, "$: " );
	strcpy( dir_home, getenv( "HOME" ) );
	getcwd( dir_cur, MEM_MAX );

	return 0;
}

/* loop the shell prompt to the user */
int shell_prompt()	{	
	/* Loop Prompt Indefinitely*/
	while( 1 )
	{
		/* Working Dir is only displayed when stdin is a terminal */
		if( show_prompt == true )
		{
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
		else
		{
			LL *head; head = NULL;
			if( ( shell_cmd_in(&head) ) == 0 )
				continue;
			else
				return 1;
		}
		

	}
	return 0;
}

/* checks for a alphanumeric character in a string */
int alphaCheck( char *cmd_line )	{
	
	int i, alNumFlag; 
	alNumFlag = 0; // 1 means there are alnums, 0 means no alnums

	for( i = 0; i < strlen( cmd_line ); i++ ) {
		if( isalnum( cmd_line[ i ] ) )
			alNumFlag = 1;
	}

	return alNumFlag;
}

/* accept command line input for the shell */
int shell_cmd_in( LL **head )	{

	char cmd_line[ MEM_MAX ];
	memset( cmd_line, 0, MEM_MAX );

	if ( fgets( cmd_line, MEM_MAX, stdin ) == NULL ){
		return 1;
	}

	/* Replacing trailing newline with a terminating nullchar */
	size_t ln = strlen( cmd_line ) - 1;
	if ( cmd_line[ ln ] == '\n' )
		cmd_line[ ln ] = '\0';

	// if the entire string doesn't have any alpha numerics, then just print another prompt
	int alphaNumFlag;
	alphaNumFlag = alphaCheck( cmd_line );
		
	if( alphaNumFlag == 1 )	{		
		newTok( cmd_line, head ); // head should now have a list of commands
		execute( *head );
	}

	return 0;
}