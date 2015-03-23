#ifndef TYPES_H
#define TYPES_H

/* */
typedef enum { 
	false,
	true
} boolean;


/* */
typedef struct linkedList {
        char command[2048];
        char args[50][2048];
        struct linkedList *next;
} LL;

/* */
typedef struct builtins{
	char *name;
	int (*f)();
} builtins;

/* */
#define FREE(ptr) 	\
do{ 				\
free((ptr)); 		\
(ptr)=NULL; 		\
}while(0) 

#endif

