#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


int length(LL *head) {

	int count;
	count = 0;
	while(head != NULL) {
		head = head->next;
		count++;
	}

	return count;

}


void destroy(LL *head) {

	LL *forward = head->next;

	while(head != NULL) {
		free(head);
		head = forward;
		if(forward == NULL)
			forward = NULL;
		else
			forward = forward->next;

	}
}

void print(LL *node) {

	printf("%s\n",node->command);
	char null[2048];
	memset(null,'\0',2048);
		
	int i;
	i = 0;
	while((strcmp(node->args[i],null)) != 0) {
		printf("%s\n",node->args[i]);		
		i++;
	}

	printf("\n");

}

void printList(LL *head) {

	while(head != NULL) {
		print(head);
		head = head->next;
	}
}

void initNode(LL *newNode,char tokens[][2048]) {

	char null[2048];
	memset(null,'\0',2048);

	// Copy command into struct	
	strcpy(newNode->command,tokens[0]);

	// Copy the args in
	int i; i = 1;
	while(strcmp(tokens[i],null) != 0) {
		strcpy(newNode->args[i-1],tokens[i]);
		i++;
	}
	
	// Set next to null
	newNode->next = NULL;
}


void insert(LL **head, char tokens[][2048]) {

	// Find the last node
	LL *end; end = *head;
	LL *newNode;
	
	if(end == NULL) {
		// special case
		// create space for a new node
		newNode = (LL *)malloc(sizeof(LL));
		initNode(newNode,tokens);
		*head = newNode;
	} else {
		while(end->next != NULL)
			end = end->next;

		// create space for a new node
		newNode = (LL *)malloc(sizeof(LL));

		// init the node
		initNode(newNode,tokens);
	
	
		// Set previous node's next to the new node
		end->next = newNode;
	}	
}
		

