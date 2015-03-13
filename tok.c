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
	if( args == NULL )
	{
		return 1;
	}

	char *iter = args;
	char token[2048];
	int i = 0;
	int j = 0;
	int offset = 0;
	char fuck[50][2048];
	
	//printf("len: %zu\nlen: %zu", strlen(args), strlen(iter));
	
	while( *iter )
	{
		//printf("c: %c\n", *iter);
		if( (*iter) == '\"' )			/* match double quotes 		*/
		{
			iter++;
			offset = shell_tok_dquote( iter );
			if( offset == 0 )
			{
				printf("mismatch\n");
			}
			else
			{
				while( offset > 1 && *iter )
				{
					token[i] = (*iter);
					iter++;
					i++;
					offset--;
				}
				iter++;
			}
			offset = 0;
			printf("token: %s\n", token);
			strcpy( fuck[j], token );
			j++;
			memset(token, 0, 2048);
			i = 0;		}
		else if( (*iter) == '\'' )		/* match single quotes 		*/
		{
			iter++;
			offset = shell_tok_squote( iter );
			if( offset == 0 )
			{
				printf("mismatch\n");
			}
			else
			{
				while( offset > 1 && *iter )
				{
					token[i] = (*iter);
					iter++;
					i++;
					offset--;
				}
				iter++;
			}
			offset = 0;
			printf("token: %s\n", token);
			strcpy( fuck[j], token );
			j++;
			memset(token, 0, 2048);
			i = 0;
		}
		else if( (*iter) == '|' )		/* token at pipe 			*/
		{
			if( i == 0)
			{
				iter ++;
			}
			else
			{
				iter++;
				printf("token: %s\n", token);

				//ins_node( fuck, list );

				memset(token, 0, 2048);
				i = 0;
			}
		}
		else if( (*iter) == ' ' || (*iter) == '\t' )	/* token at space or tab 	*/
		{
			if( i == 0)
			{
				iter++;
			}
			else
			{
				iter++;
				printf("token: %s\n", token);
				memset(token, 0, 2048);
				i = 0;
			}
		}
		else
		{
			token[i] = (*iter);
			iter++;
			i++;
		}
		



	}
	printf("token: %s\n", token);

}

int shell_tok_dquote( char* cmd_line )
{
	char *iter = cmd_line;
	int char_count = 0;

	while( *iter )
	{
		char_count++;
		if( ( *iter ) == '\"' )
		{
			return char_count;
		}
	
					
		iter++;
	}
	return 0;
}

int shell_tok_squote( char* cmd_line )
{
	char *iter = cmd_line;
	int char_count = 0;

	while( *iter )
	{
		char_count++;		
		if( ( *iter ) == '\'' )
		{
			return char_count;
		}
		iter++;
	}
	return 0;
}