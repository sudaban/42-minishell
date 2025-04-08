#include <stdio.h>
#include <stdlib.h>

int	builtin_exit(char **args)
{
	(void)args;
	printf("exit\n");
	exit(0);
}