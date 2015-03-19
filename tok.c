#include "defs.h"

#include "types.h"

#include <string.h>

#include <stdio.h>



int shell_tok( char* args, LList** list )	{	 

	if( args == NULL )	{

		return 1;

	}



	char *iter = args;

	char token[2048];

	int i = 0;

	int offset = 0;

	

	LList *new_node;





	/* Loop through each char to null char*/

	while( *iter )	{

		new_node = (LList*)malloc(sizeof(LList));

		/* match double quotes */

		if( (*iter) == '\"' || (*iter) == '\'' )	{



			offset = shell_tok_match_len( iter, (*iter) );

			iter++;



			/* if no matching quote is found */

			if( offset == 0 )	{

				printf("mismatch\n");

			}

			else	{

				while( offset > 1 && *iter )	{

					token[i] = (*iter);

					iter++;

					i++;

					offset--;

				}

				iter++;

			}

			offset = 0;



			memset(token, 0, 2048);

			i = 0;		

		}

		/* pipe found, should end command-argument block here */

		else if( (*iter) == '|' )	{

			if( i == 0)	{

				iter ++;

			}

			else	{

				llist_ins( list, token );

				iter++;

				memset(token, 0, 2048);

				i = 0;

			}

		}

		/* space or tab found */

		else if( (*iter) == ' ' || (*iter) == '\t' )	{

			if( i == 0)	{

				iter++;

			}

			else	{

				iter++;

				memset(token, 0, 2048);

				i = 0;

			}

		}

		/* add char to the token string */

		else	{

			token[i] = (*iter);

			iter++;

			i++;

		}

	}



	if( strcmp( token, "\0" ) != 0 )

		printf("token: %s\n", token);

	memset(token, 0, 2048);



}



int shell_tok_match_len( char* cmd_line, char match )	{



	char *iter = cmd_line;

	int char_count = 0;



	while( *iter )	{

		char_count++;

		if( ( *iter ) == match )

			return char_count;

		iter++;

	}

	return 0;

}
