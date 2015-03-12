#ifndef HEADERS_H
#define HEADERS_H

#include "types.h"

#define MAKE_RED "\e[31m"
#define RESET_FORMAT "\e[m"

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


/* isstdio.c */
	int is_std_i();
	int is_std_o();

#endif
