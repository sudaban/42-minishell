/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:31:10 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:28:37 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Built-In/Cd/cd.h"
#include "Built-In/Echo/echo.h"
#include "Built-In/Env/env.h"
#include "Built-In/Exit/exit.h"
#include "Built-In/Export/export.h"
#include "Built-In/Pwd/pwd.h"
#include "Built-In/Unset/unset.h"
#include "Executor/executor.h"
#include "Lexer/lexer.h"
#include "Libft/libft.h"
#include "Parser/parser.h"
#include "Signal/signal.h"
#include "Utils/Memory/memory.h"
#include "Utils/Status/status.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	process_input(char *input, t_shell *shell)
{
	(void)shell;
	if (!input)
	{
		printf("exit\n");
		return (0);
	}
	if (!check_syntax(input))
	{
		set_exit_status(2);
		free(input);
		return (1);
	}
	if (*input)
		add_history(input);
	return (2);
}

static void	process_command(char *input, t_shell *shell)
{
	char		**splitted;
	t_token		*tokens;
	t_ast_node	*ast;

	splitted = lexer_split(input, ' ', shell);
	tokens = lexer(splitted);
	ast = parse_tokens(tokens, shell);
	if (shell->debug)
	{
		print_token_debug(tokens);
		printf("--------------------------------------------------\n");
		print_ast_debug(ast);
	}
	execute_ast(ast, shell);
	memory_free(tokens);
	memory_free(ast);
	free(input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;
	int		status;

	(void)argc;
	shell.env = envp;
	shell.debug = (argv[1] && !ft_strncmp(argv[1], "-d", 3));
	while (1)
	{
		set_signal_handler(0);
		input = readline("Born2Exec$ ");
		shell.should_expand = true;
		status = process_input(input, &shell);
		if (status == 0)
			break ;
		else if (status == 1)
			continue ;
		process_command(input, &shell);
	}
	memory_cleanup(0);
	return (0);
}
