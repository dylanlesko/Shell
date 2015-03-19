#ifndef TYPES_H

#define TYPES_H





/* */

typedef enum { 

	false,

	true

} boolean;







/* */

typedef struct LList

{

	char command[2048];

	char args[50][2048];

	int arg_count;

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

