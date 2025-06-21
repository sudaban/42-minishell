/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:31:10 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/21 17:23:25 by sdaban           ###   ########.fr       */
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
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Utils/Status/status.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*input;
	t_token		*tokens;
	t_ast_node	*ast;

	(void)argc;
	shell.env = envp;
	shell.debug = (argv[1] && !ft_strncmp(argv[1], "-d", 3));
	setup_signals();

	while (1)
	{
		input = readline("Born2Exec$ ");
		shell.should_expand = true;
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (!check_syntax(input))
		{
			set_exit_status(2);
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);

		tokens = lexer(input);
		ast = parse_tokens(tokens, &shell);

		if (shell.debug)
		{
			print_token_debug(tokens);
			printf("--------------------------------------------------\n");
			print_ast_debug(ast);
		}
		execute_ast(ast, &shell);
		memory_free(tokens);
		memory_free(ast);
		free(input);
	}
	rl_cleanup_after_signal();
	rl_clear_history();
	memory_cleanup();
	return (0);
}



// TO DO : env memory checking hsamir
// ADD Input to memory list

/*
file name should be alphabetic or numeric after redirection
*/