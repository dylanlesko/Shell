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
			if(tokNum < 51) {
	                        tokens[tokNum][i] = *iter;
	                        i++; iter++;
			} else {
				fprintf(stderr,"Too many arguments.\n");
				return (LL **)NULL;
			}
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

