#include "export.h"
#include <unistd.h>

int	builtin_export(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
			write(2, "export: not a valid identifier\n", 31);
		else if (!replace_env(args[i], &shell->env))
			shell->env = append_env(args[i], shell->env);
		i++;
	}
	return (0);
}
