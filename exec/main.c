#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"



int main() {

	LL *first = (LL *)malloc(sizeof(LL));
	LL *second = (LL *)malloc(sizeof(LL));
	LL *third = (LL *)malloc(sizeof(LL));
	LL *fourth = (LL *)malloc(sizeof(LL));
	LL *fifth = (LL *)malloc(sizeof(LL));
	LL *sixth = (LL *)malloc(sizeof(LL));
	LL *seventh = (LL *)malloc(sizeof(LL));
	LL *eighth = (LL *)malloc(sizeof(LL));

	strcpy(first->command,"cat");
	strcpy(first->args[0],"/home/nikhil/Documents/School/spring2015/os/homework/Shell/exec/moby.txt");
	first->next = second;


	strcpy(second->command,"tr");
	strcpy(second->args[0],"A-Z");
	strcpy(second->args[1],"a-z");
	second->next = third;

		
	strcpy(third->command,"tr");
	strcpy(third->args[0],"-C");
	strcpy(third->args[1],"a-z");
	strcpy(third->args[2],"\n");
	third->next = fourth;
	
	strcpy(fourth->command,"sed");
	strcpy(fourth->args[0],"/^$/d");
	fourth->next = fifth;

	strcpy(fifth->command,"sort");
	fifth->next = sixth;

	strcpy(sixth->command,"uniq");
	strcpy(sixth->args[0],"-c");
	sixth->next = seventh;

	strcpy(seventh->command,"sort");
	strcpy(seventh->args[0],"-nr");
	seventh->next = eighth;

	strcpy(eighth->command,"sed");
	strcpy(eighth->args[0],"10q");
	eighth->next = NULL;


	execute(first);

	destroy(first);

	return 0;
}



