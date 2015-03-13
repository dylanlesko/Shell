#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
#include "types.h"


boolean show_prompt = true;
char dir_home[ MEM_MAX ];
char dir_cur[ MEM_MAX ];
char prompt[ 2 ];


void shell_exit(void)
{
	printf("\n\n");
}

/* */
int main()
{
	atexit(shell_exit);
	LList **argsLL = ( LList** )malloc( sizeof( LList ) );
	//test();


	if ( (shell_init( ) ) == 0 )
	{
		shell_prompt( argsLL );
	}

	exit( 0 );
}

/* */
int shell_init()
{
	
	if( is_std_i() == true )
	{
		show_prompt = true;
		strcpy( prompt, "$: " );
		strcpy( dir_home, getenv( "HOME" ) );
		getcwd( dir_cur, MEM_MAX );
		//printf( "prompt: %s\nhome: %s\ncur: %s\n", prompt, dir_home, dir_cur );

		return 0;
	}
	else
	{
		printf("std in not a terminal\n");
		return 1;
	}
	return 1;
}

/* */
int shell_prompt( LList** list )
{	
	while( show_prompt == true )
	{
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
int shell_cmd_in( LList** list )
{
	char cmd_line[ MEM_MAX ];
	memset( cmd_line, 0, MEM_MAX );

	if ( fgets( cmd_line, MEM_MAX, stdin ) == NULL )
	{
		return 1;
	}

	shell_tok( cmd_line, list );

	//cmd_line_format( cmd_line );

	return 0;
}

/* */
int cmd_line_format( char* cmd_line )
{
	fputs(cmd_line, stdout ) ;
	shell_tok( cmd_line, NULL );
}

int test( )
{






















}

