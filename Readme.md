Stuff to implement:

-parsing into a command list
	- | then "" and '' then space
-print prompt only if the input is a terminal (use isatty(0))

-built in commands
	- cd dirname
	-exit
-pipe using the pipe system call
?what happens if the pip is inside a quote. so ' command "some|thing" '

-built in commands based on a list, check before exec

DO NOT NEED
-commands that span multiple lines
-environment vars
-multiple commands per line, ie dothis;dothat;dothis
-IO redirection, ie ">outfile"

# To Do

## 1. Command Prompt
	Start Shell
	Check if stdio is terminal

## 2. Command Line Parse
	Create a structure, see Struct Section
	Parse list based off of commands
	Group arguments based off of pairs of quotations or white space
	

## 3. Command Execution
	Create internal command list
	Check if command is a built in command
	fork
	exec

# Struct Example #
	| Command 1   ->| Command 2  -> | Command 3   -> |  NULL |
	| ------------- |:-------------:| -----:         |       |
	| c1 arg1       | c2 arg 1      | c3 arg 1       |       |
	| c1 arg2       | c2 arg 2      |                |
	| c1 arg 3      | c2 arg 3      |                |

> typedef Struct linkedlist{  
>>char command[2048];  
char args[50][2048];  
struct linkedList *next;  

> } linkedList;
