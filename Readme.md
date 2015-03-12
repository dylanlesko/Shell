Shell Project
=============
####Version 0.1

# To Do

### 1. Command Prompt
	Loops in terminal accepting input as commands and arguments
* Start Shell
* Check if stdio is terminal with isatty(0)

### 2. Command Line Parse
	Format the user input so that we can execute their commands
* Create a structure, see Struct Section
* Parse list based off of commands
* Group arguments based off of pairs of quotations or white space
	

### 3. Command Execution
	Manage process execution and termination
* Create internal command list
* Check if command is a built in command
* fork
* exec
* parent waits

### 4. Do Not Need
* commands that span multiple lines
* environment vars
* multiple commands per line, ie dothis;dothat;dothis
* IO redirection, ie ">outfile"

# Built in Commands
### 1. CD  
	Change directory
### 2. Exit
	Exit command, return value to terminal

# Struct Example #
	| Command 1   ->| Command 2  -> | Command 3   -> |  NULL |
	| ------------- |:-------------:| -------------: |       |
	| c1 arg1       | c2 arg 1      | c3 arg 1       |       |
	| c1 arg2       | c2 arg 2      |                |       |
	| c1 arg 3      | c2 arg 3      |                |       |

> typedef Struct linkedlist{  
>>char command[2048];  
char args[50][2048];  
struct linkedList *next;  

> } linkedList;
