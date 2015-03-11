#ifndef TYPES_H
#define TYPES_H


/* */
typedef enum { 
	false,
	true
} boolean;




/* */
typedef struct AList
{
	char* argument;
	struct AList *next;
} AList;

/* */
typedef struct LList
{
	struct AList **arguments;
	struct LList *next;
} LList;

/* */
typedef char* stringStructPtr;

/* */
#define FREE(ptr) 	\
do{ 				\
free((ptr)); 		\
(ptr)=NULL; 		\
}while(0) 


#endif
