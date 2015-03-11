#include "defs.h"
#include "types.h"
#include <string.h>
#include <stdio.h>

/*
 * 1) Create Tokenizer
 * 		a) Generate tokens based off of quotations
 * 		b) Parse tokens based off of pipe
 * 		c) Parse the final subset based off of spaces and tabs
 * 
 * 2) 
 * 
 * 
 * 
 * 
 */
 
int shell_tok( char* args, LList** list )
{
	
	/*
	 * 	char *strpbrk(const char *str1, const char *str2)
	 */
	 
	if( args == NULL )
	{
		return 1;
	}

	char *iter = args;
	char token[2048];
	int i = 0;
	
	
	
	while( *iter )
	{
		//printf("c: %c\n", *iter);
		iter++;
		if( (*iter) == '\"' )			/* match double quotes 		*/
		{
		}
		else if( (*iter) == '\'' )		/* match single quotes 		*/
		{
		}
		else if( (*iter) == '|' )		/* token at pipe 			*/
		{
			printf("terminated\n");
		}
		else if( (*iter) == ' ' 
			|| (*iter) == '\t' )		/* token at space or tab 	*/
		{
			printf("terminated\n");
		}
		else
		{
			token[i] = (*iter);
		}
		
		i++;
	}

}
