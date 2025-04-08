#include <unistd.h>
#include <stdio.h>

int	builtin_pwd(char **args)
{
	char	cwd[1024];

	(void)args;
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
	return (0);
}
