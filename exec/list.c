#include <stdio.h>
#include <stdlib.h>
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
	
	int i;
	i = 0;
	while((strcmp(node->args[i],"")) != 0) {
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

