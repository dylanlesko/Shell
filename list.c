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
int ins_node( char* arg, LList **head )
{
	if( ( *head ) == NULL )
	{
		( *head ) = malloc( sizeof( LList ) );
		//( *head )->ele = string_init( arg );
		( *head )->next = NULL;
	}
	else
	{
		ins_node( arg, &( (*head)->next ) );
	}
	return 0;
}

/* */
int ins_llist( char* arg, LList **head )
{
	if( ( *head ) == NULL )
	{
		( *head ) = malloc( sizeof( LList ) );
	}
	else
	{
		ins_llist( arg, &( (*head)->next ) );
	}
	return 0;
}

/* */
int dump_llist( LList *head )
{
	if(head == NULL)
	{
		return 0;
	}
	
	//printf("arg: %s\n", head->arg);
	dump_llist( head->next );
}

/* */
int free_llist( LList *head )
{
	if(head == NULL)
		return;
		
	LList *iter = head;
	LList *temp;
	
	while (iter != NULL)
	{
		temp = iter;
		iter = iter->next;
		//free_alist( temp->arguments );
		FREE(temp);
	}
	head = NULL;
}