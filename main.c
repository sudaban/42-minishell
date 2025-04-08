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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*input;
	char	*args[100];
	int		i;

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
			if (strcmp(args[0], "exit") == 0)
				builtin_exit(args);
			else if (strcmp(args[0], "pwd") == 0)
				builtin_pwd(args);
			else if (strncmp(args[0], "echo", 5) == 0)
				builtin_echo(args);
			else if (strncmp(args[0], "cd", 3) == 0)
				builtin_cd(args);
			else if (strncmp(args[0], "env", 4) == 0)
				builtin_env(envp);
			else
				printf("Command not found: %s\n", input);
		}
		free(input);
	}
	return (0);
}
