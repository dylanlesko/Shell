#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "types.h"

/* returns length of the list */
int length( LL *head ) {

	int count;
	count = 0;
	while( head != NULL ) {
		head = head->next;
		count++;
	}

	return count;
}

/* free allocated memory for a list */
void destroy( LL *head ) {

	LL *forward = head->next;

	while( head != NULL ) {
		free(head);
		head = forward;
		if( forward == NULL )
			forward = NULL;
		else
			forward = forward->next;
	}
}

/* */
void print( LL *node ) {

	printf( "%s\n", node->command );
	char null[ MEM_MAX ];
	memset( null, '\0', MEM_MAX );
		
	int i = 0;
	while( (strcmp( node->args[i], null )) != 0 ) {
		printf( "%s\n", node->args[ i ] );		
		i++;
	}

	printf( "\n" );
}

/* */
void printList( LL *head ) {

	while( head != NULL ) {
		print( head );
		head = head->next;
	}
}

/* initialize a linkedlist */
void initNode( LL *newNode, char tokens[][ MEM_MAX ] ) {

	char null[ MEM_MAX ];
	memset( null, '\0', MEM_MAX );

	// Copy command into struct	
	strcpy( newNode->command, tokens[ 0 ] );

	// Copy the args in
	int i = 1;
	while( strcmp( tokens[ i ], null ) != 0 ) {
		strcpy( newNode->args[ i-1 ], tokens[ i ] );
		i++;
	}
	
	// Set next to null
	newNode->next = NULL;
}

/* insert a node into a linked list */
void insert( LL **head, char tokens[][ MEM_MAX ] ) {

	// Find the last node
	LL *end;
	end = *head;
	LL *newNode;
	
	if( end == NULL ) {
		// special case
		// create space for a new node
		newNode = ( LL * )malloc( sizeof( LL ) );
		initNode( newNode,tokens );
		*head = newNode;
	} else {
		while(end->next != NULL)
			end = end->next;

		// create space for a new node
		newNode = ( LL * )malloc( sizeof( LL ) );

		// init the node
		initNode( newNode,tokens );

		// Set previous node's next to the new node
		end->next = newNode;
	}	
}