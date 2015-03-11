#ifndef HEADERS_H
#define HEADERS_H

#include "types.h"

/* shell.c */
int 
	fakeShell		( 										
	);
int 
	processSTDIO	( char* args, 		LList **root 					
	);


/* tok.c */
int 
	shell_tok		( char* args, 		LList** list 					
	);

/* list.c */
stringStructPtr
	string_init 	( char* string 
	);



#endif
