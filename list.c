#include "defs.h"

#include "types.h"

#include <stdlib.h>

#include <stdio.h>

#include <string.h>



/* */

stringStructPtr string_init ( char* string )

{	

	if( string == NULL )

	{

		return NULL;

	}

	

	stringStructPtr newStruct = ( stringStructPtr ) malloc( strlen( string ) + 1 );

		strcpy( newStruct, string );

		( newStruct )[ strlen( string ) ] = '\0';

		

	return newStruct;

}





/* */

int llist_ins( char* cmd, LList **head )

{

	if( ( *head ) == NULL )

	{

		( *head ) = malloc( sizeof( LList ) );

		( *head )->arg_count = 0;

		strcpy( ( *head )->command, cmd );

		( *head )->next = NULL;

	}

	else

	{

		llist_ins( cmd, &( (*head)->next ) );

	}

	return 0;

}





/* */

int llist_ins_arg( LList *list, char* arg)

{

	strcpy( list->args[list->arg_count], arg);

	list->arg_count = list->arg_count + 1;



}



/* */

int llist_dump( LList *list )

{



}



/* */

int llist_free( LList *list )

{

	

}
