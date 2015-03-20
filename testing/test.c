#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
#include "types.h"
#include "list.c"

int main() {


	LList **head = (LList **)malloc(sizeof(LList));
	llist_ins("ls",head);
	llist_ins_arg(*head,"~/Documents");


	return 0;
}
