#include <stdlib.h> /* needed for exit() */
#include <unistd.h> /* needed for isatty() */
#include <stdio.h> /* needed for printf() */
#include "types.h"

int is_std_i()
{
	if (isatty(0)) 
	{
		//printf("the standard input is from a terminal\n");
		return true;
	}
	else
	{
		//printf("the standard input is NOT from a terminal\n");
		return false;
	}
}

int is_std_o()
{
	if (isatty(1))
	{
		//printf("the standard output is to a terminal\n");
		return true;
	}
	else
	{ 
		//printf("the standard output is NOT to a terminal\n");
		return false;
	}
	

}