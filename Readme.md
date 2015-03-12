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
