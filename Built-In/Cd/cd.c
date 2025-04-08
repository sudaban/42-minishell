#include "cd.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	builtin_cd(char **args)
{
	char	*path;
	char	*home;

	if (!args[1]) // only cd
	{
		home = getenv("HOME");
		if (!home)
		{
			write(2, "cd: HOME not set\n", 18);
			return (1);
		}
		path = home;
	}
	else
		path = args[1];

	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
