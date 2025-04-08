#include <unistd.h>
#include <string.h>

int	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strchr(envp[i], '='))
		{
			write(1, envp[i], strlen(envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
