#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "types.h"

extern char dir_home[ MEM_MAX ];
extern char dir_cur[ MEM_MAX ];

/* */
int our_exit(char args[ 50 ][ MEM_MAX ] ) {
	if( args == NULL ) {
		exit( 0 );
	}

	exit( atoi( args[ 0 ] ) );
}

/* */
int our_cd( char dir[ 50 ][ MEM_MAX ] ) {

	char Null[ MEM_MAX ];
	memset( Null, '\0', MEM_MAX );
	if( strcmp( dir[ 0 ], Null ) == 0 ) {
		chdir( dir_home );	
		memset( dir_cur, '\0', MEM_MAX );
		strcpy( dir_cur, dir_home );
		return 0;
	}

	if( strlen( dir[ 1 ] ) > 0 ) {
		fprintf( stderr, "\ncd: too many arguments\n" );
		return 0;
	}
	
	char null[ 1024 ];
	memset( null, 0, 1024 );

	char cwd[ 1024 ];
	if( strncmp( dir[ 0 ], "/", 1) != 0 ) {
		if ( getcwd( cwd, sizeof( cwd ) ) != 0 ) {

			char path[ MEM_MAX ];
			strcpy( path, cwd );
			strcat( path, "/" );
			strcat( path, dir[ 0 ] );
			chdir( path );
			memset( dir_cur, '\0', MEM_MAX );
			strcpy( dir_cur, path );
		}
		else {
			perror( "getcwd() error" );
		}
	}
	else {
		chdir( dir[ 0 ] );
		memset( dir_cur, '\0', MEM_MAX );
		strcpy( dir_cur, dir[ 0 ] );
	}
	
	char cwd2[ 1024 ];
	getcwd( cwd2, sizeof( cwd2 ) );
	printf( "now in dir %s\n", cwd2 );
}

struct builtins** builts;
/* */
void prepfs() {
	builts = (struct builtins**)malloc(2*sizeof(struct builtins));
	builts[0] = (struct builtins*)malloc(sizeof(struct builtins));
	builts[1] = (struct builtins*)malloc(sizeof(struct builtins));	
	((struct builtins*)builts[0])->name = "cd";
	((struct builtins*)builts[1])->name = "exit";
	((struct builtins*)builts[0])->f = &our_cd;
	((struct builtins*)builts[1])->f = &our_exit;
}

/* */
int builtIn( LL *cmd ) {
	
	int i;
	for( i = 0; i < 2; i ++ ) {
		if(strcmp(cmd->command, ((struct builtins*)builts[i])->name) == 0) {
			((struct builtins*)builts[i])->f(cmd->args);
			return 1;
		}
	}
	return 0;
}

/* */
void prepForExec(char *Args[], LL *node) {
	
	Args[0] = node->command;

	char null[MEM_MAX];
	memset(null,'\0',MEM_MAX);

	int i;
	i = 0;
	while( (strcmp( node->args[ i ], "") ) != 0 ) {
		Args[ i+1 ] = node->args[ i ];
		i++;
	}

	Args[ i+1 ] = NULL;

	return;
}

/* */
void closeFDsingle( int fd, int pipes[][2], int pipeNum ) {

        int i, j;
        for( i = 0; i < pipeNum; i++ ) {
                for( j = 0; j < 2; j++ ) {
                        if( pipes[ i ][ j ] != fd )
                                close( pipes[ i ][ j ] );
                }
        }
}

/* */
void closeFDdouble( int one, int two, int pipes[][2], int pipeNum ) {

        int i, j;
        for( i = 0; i < pipeNum; i++ ) {
                for( j = 0; j < 2; j++ ) {
                        if( ( pipes[ i ][ j ] != one ) && ( pipes[ i ][ j ] != two ) )
                                close( pipes[ i ][ j ] );
                }
        }
}

/* */
int builtInCheck( LL *cmd ) {

	int i;
	for( i = 0; i < 2; i++ ) {
		if( strcmp( cmd->command, ( (struct builtins* )builts[i])->name ) == 0 )
			return 1;
	}
	return 0;
}

/* */
void execute( LL *head ) {

	int status;
	LL *cmd;
	cmd = head;
	pid_t pid;

	int pipeNum,listLen;
	listLen = length( head );
	pipeNum = listLen - 1;
	int pipes[ pipeNum ][ 2 ];

	int i;
	for(i = 0; i < pipeNum; i++)
		pipe( pipes[ i ] );

	for( i = 0; i < listLen; i++ ) {
		switch( pid = fork() ) {
			case 0:
				if( i == 0 ) { // beginning
					if( builtInCheck( cmd ) ) {
						exit( 0 );
					} 
					else {
						dup2( pipes[ i ][ 1 ], 1 );
						closeFDsingle( pipes[ i ][ 1 ], pipes, pipeNum );
						char *Args[ ARG_MAX ];
						prepForExec( Args, cmd );
						execvp( Args[ 0 ], Args );
						perror( Args[ 0 ] );
						exit( 1 );
					}
				}
				else if( i == pipeNum ) { // end
					if( builtInCheck( cmd ) ) {
						exit( 0 );
					}
					else {
						dup2( pipes[ i-1 ][ 0 ], 0 );
						closeFDsingle( pipes[ i-1 ][ 0 ], pipes, pipeNum );
						char *Args[ ARG_MAX ];
						prepForExec( Args, cmd );
						execvp( Args[ 0 ], Args );
						perror( Args[ 0 ] );
						exit( 1 );
					}
				}
				else { // middle
					if( builtInCheck( cmd ) ) {
						exit( 0 );
					}
					else {
						dup2( pipes[ i-1 ][ 0 ], 0 );
						dup2( pipes[ i ][ 1 ], 1 );
						closeFDdouble(pipes[i-1][0],pipes[i][1],pipes,pipeNum);
						char *Args[ ARG_MAX ];
						prepForExec( Args, cmd );
						execvp( Args[ 0 ], Args );
						perror( Args[ 0 ] );
						exit( 1 );
					}
				}

                  default:
				if( builtInCheck( cmd ) ) {
					builtIn( cmd );
				}

				if( i < pipeNum ) {
					close( pipes[ i ][ 1 ] ); //close(pipes[i][0]);
					cmd = cmd->next;
				}
				break;

			case -1:
				perror( "fork" );
				exit( 1 );
                }
        }

	 while((pid = wait(&status)) != -1)
                fprintf(stderr,"Process %d exits with %d\n",pid,WEXITSTATUS(status));
}