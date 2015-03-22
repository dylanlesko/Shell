#ifndef LIST_H
#define LIST_H

#include <stdio.h>

struct linkedList {
        char command[2048];
        char args[50][2048];
        struct linkedList *next;
};

typedef struct linkedList LL;

int length(LL *head);
void destroy(LL *head);
void print(LL *node);
void printList(LL *head);
void insert(LL **head,char tokens[][2048]);
void initNode(LL *newNode,char tokens[][2048]);


#endif
