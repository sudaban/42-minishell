#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include "Signal/signal.h"
#include "Built-In/Exit/exit.h"
#include "Built-In/Pwd/pwd.h"
#include "Built-In/Echo/echo.h"
#include "Built-In/Cd/cd.h"
#include "Built-In/Env/env.h"
#include "Built-In/Export/export.h"
#include "Built-In/Unset/unset.h"
#include "minishell.h"

static void	execute_command(char **args, t_shell *shell)
{
	if (strcmp(args[0], "exit") == 0)
		builtin_exit(args);
	else if (strcmp(args[0], "pwd") == 0)
		builtin_pwd(args);
	else if (strncmp(args[0], "echo", 5) == 0)
		builtin_echo(args);
	else if (strncmp(args[0], "cd", 3) == 0)
		builtin_cd(args);
	else if (strncmp(args[0], "env", 4) == 0)
		builtin_env(shell->env);
	else if (strncmp(args[0], "export", 7) == 0)
		builtin_export(args, shell);
	else if (strncmp(args[0], "unset", 6) == 0)
		builtin_unset(args, shell);
	else
		printf("Command not found: %s\n", args[0]);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_shell	shell;
	char	*input;
	char	*args[100];
	int		i;

	shell.env = envp;

	// Setup signal handlers
	setup_signals();

	while (1)
	{
		input = readline("aamonshell$ ");
		if (!input) // ctrl-D (EOF)
		{
			printf("exit\n");
			free(input);
			break;
		}
		if (*input)
			add_history(input);

		i = 0;
		char *token = strtok(input, " ");
		while (token)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		if (args[0])
		{
			execute_command(args, &shell);
		}
		free(input);
	}
	return (0);
}
