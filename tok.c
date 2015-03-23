#include "defs.h"
#include "types.h"
#include <string.h>
#include <stdio.h>

int shell_tok_match_len( char* cmd_line, char match )   {

        char *iter = cmd_line;
        int char_count = 0;

        while(*iter != '\0')  {
                char_count++;
                if(*iter == match)
                        return char_count;
                iter++;
        }
}


int addArg(LL *node, char *new){
	//printf("adding arg%s",new);
	int i = 0;
	while(strlen(node->args[i])!=0){
		i++;
	}
	strcpy(node->args[i],new);

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

/*
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
	
	 Loop through each char to null char
	while( *iter )	{
		if(startnew == true){	
			LL* next_node;
			next_node = (LL*)malloc(sizeof(LL));
			next_node = (LL*)malloc(sizeof(LL));
			cur_node->next = next_node;
			cur_node = next_node;
			startnew = false;
		}
		 match double quotes 
		if( (*iter) == '\"' || (*iter) == '\'' )	{

			offset = shell_tok_match_len( iter, (*iter) );
			iter++;

			 if no matching quote is found 
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
		 pipe found, should end command-argument block here 
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
		 space or tab found 
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
		 add char to the token string 
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

        return 0;
}

*/

void condense(char tokens[][2048]) {

        char null[2048];
        memset(null,'\0',2048);

        int nonNullCount; nonNullCount = 0;
        int i;
        // Find out how many non-null strings there are
        for(i = 0; i < 51; i++) {
                if(strcmp(tokens[i],null) != 0)
                        nonNullCount++;
        }

        int j;
        for(i = 0; i < nonNullCount; i++) {
                if(strcmp(tokens[i],null) == 0) {
                        for(j = i; j < 51; j++) {
                                if(strcmp(tokens[j],null) != 0)
                                        break;
                        }

                        strncpy(tokens[i],tokens[j],2048); // move the string
                        memset(tokens[j],'\0',2048);
                }
        }

}


void printTokens(char tokens[][2048]) {

        char null[2048];
        memset(null,'\0',2048);

        printf("\n");

        int i;
        for(i = 0; i < 51; i++) {
                if(strcmp(tokens[i],null) != 0)
                        printf("%s\n",tokens[i]);
        }

        printf("\n");


}

void shiftCmd(char *cmd_line) {

        char buffer[2048];

        char *real;
        real = cmd_line;
        while(*real == ' ')
                real++;

        strncpy(buffer,real,strlen(real));
        strcpy(cmd_line,buffer);

}


LL **newTok(char *cmd_line,LL **head) {

        char tokens[51][2048];
	memset(tokens,'\0',51*2048);
        char *iter = cmd_line;
        int offset, tokNum, i;
        tokNum = 0; i = 0; offset = 0;

        // set cmd_line[0] to non-null
        if(*cmd_line == ' ')
                shiftCmd(cmd_line);

        while(*iter != '\0') {

                if(*iter == ' ') {
                        if(cmd_line[0] == *iter)
                                iter++;
                        else if(*(iter-1) != ' ') {
                                if(**tokens == '\0') // no tokens yet
                                        iter++;
                                else {
                                        tokens[tokNum][i] = '\0';
                                        tokNum++; iter++;
                                        i = 0;
                                }
                        }
                        else
                                iter++;
                } else if((*iter == '\'') || (*iter == '\"')) {
                        offset = shell_tok_match_len(iter+1,*iter);
                        if(offset != 0) {
                                strncpy(tokens[tokNum],iter+1,offset-1); // gets rid of the quotes
                                tokens[tokNum][offset-1] = '\0'; // properly terminate the string
                                tokNum++;
                                iter += offset+1;
                                offset = 0;
                        } else {
                                fprintf(stderr,"No matching quote %c for command. Exiting...\n",*iter);
                                return (LL **)NULL;
                        }
                } else if(*iter == '|') {
			// Create a node with all of the tokens
                        if(*tokens == '\0') {
                                fprintf(stderr,"Error: no tokens for command\n");
                                return (LL **)NULL;
                        } else {
                                condense(tokens);
                                //printTokens(tokens);
                                //printf("Would like to call listInsert(head,tokens) to add a command to the list\n");
				insert(head,tokens);
                                memset(tokens,'\0',51*2048); // reset the token buffer to NULL
                                iter++;
                                i = 0;
                                tokNum = 0;
                        }
                }  else {
                        tokens[tokNum][i] = *iter;
                        i++; iter++;
                }
        }

	condense(tokens);
        //printTokens(tokens);
	insert(head,tokens);
	memset(tokens,'\0',51*2048); // reset the token buffer to NULL

        if(*tokens == '\0')
                printf("Insert the last set of tokens as a command\n");

	return head;
}

