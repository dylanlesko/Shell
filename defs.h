#ifndef HEADERS_H
#define HEADERS_H

#include "types.h"
#include <stdlib.h>


/* output formatting */
#define MAKE_GREEN "\e[32m"
#define MAKE_RED "\e[31m"
#define MAKE_BLACK "\e[30m"
#define MAKE_YELLOW "\e[33m"
#define MAKE_BLUE "\e[34m"
#define MAKE_PURPLE "\e[35m"
#define MAKE_CYAN "\e[36m"
#define MAKE_WHITE "\e[37m"
#define MAKE_UNDERLINE "\e[4m"
#define RESET_FORMAT "\e[m"



/* shell.c */
int fakeShell		( );
int processSTDIO	( char* args, 		LList **root 		);
void shell_exit( void );


/* tok.c */
int 
	shell_tok		( char* args, 		LList** list 					
	);

/* list.c */
stringStructPtr
	string_init 	( char* string 
	);
int free_llist( LList *head );
int dump_llist( LList *head );
int ins_llist( char* arg, LList **head );
int ins_node( char* arg, LList **head );



/* isstdio.c */
	int is_std_i();
	int is_std_o();



#define MEM_MAX ( ( size_t ) 2048 )

extern boolean show_prompts;
extern char dir_home[ MEM_MAX ];
extern char dir_cur[ MEM_MAX ];
extern char prompt[ 2 ];


#endif
