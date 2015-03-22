#include "defs.h"
#include "types.h"
#include <string.h>
#include <stdio.h>

int addArg(LL *node, char *new){
	//printf("adding arg%s",new);
	int i = 0;
	while(strlen(node->args[i])!=0){
		i++;
	}
	strcpy(node->args[i],new);
}

LL* shell_tok( char* args, LL** list )	{	 
	

	char *iter = args;
	char token[2048];
	int i = 0;
	int offset = 0;
	
	LL *new_node;
	LL *cur_node;	

	new_node = (LL*)malloc(sizeof(LL));
	cur_node = new_node;
	boolean startnew = false;


	if( args == NULL )	{
		return new_node;
	}
	
	/* Loop through each char to null char*/
	while( *iter )	{
		if(startnew == true){	
			LL* next_node;
			next_node = (LL*)malloc(sizeof(LL));
			next_node = (LL*)malloc(sizeof(LL));
			cur_node->next = next_node;
			cur_node = next_node;
			startnew = false;
		}
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
	//		printf("token: %s%zu\n", token, strlen(cur_node->command));
			
			//if there is room in the command put new token there, else its an arg
			if(strlen(cur_node->command) == 0){
				strcpy(cur_node->command, token);	
			}else{
				//loop through args and get first empty
				addArg(cur_node, token);
			}
			
			memset(token, 0, 2048);
			i = 0;		
		}
		/* pipe found, should end command-argument block here */
		else if( (*iter) == '|' )	{
			if( i == 0)	{
				iter ++;
			}
			else	{
				//llist_ins( list, token );
				iter++;
	//			printf("token: %s%zu\n", token, strlen(cur_node->command));
				//printf("token: %s\n", token);	
	//			printf("pipe is here");
				startnew = true;			
	
				if(strlen(cur_node->command) == 0){
					strcpy(cur_node->command, token);	
				}else{
					//loop through args and get first empty
					addArg(cur_node, token);
				}
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
	//			printf("token: %s%zu\n", token, strlen(cur_node->command));
				//printf("token: %s\n", token);
				
				if(strlen(cur_node->command) == 0){
					strcpy(cur_node->command, token);	
				}else{
					//loop through args and get first empty
					addArg(cur_node, token);
				}
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

	if( strcmp( token, "\0" ) != 0 ){
		//printf("token: %s\n", token);
//		printf("token: %s%zu\n", token, strlen(cur_node->command));
	}

	if(strlen(cur_node->command) == 0){
		strcpy(cur_node->command, token);	
	}else{
		//loop through args and get first empty
		addArg(cur_node, token);
	}
	memset(token, 0, 2048);
	//print(cur_node);
	//printf("\nstrting printList\n");
	//printList(new_node);
	return new_node;
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
