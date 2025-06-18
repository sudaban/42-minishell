/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:31:10 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 15:56:41 by itaskira         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*input;
	t_token		*tokens;
	t_ast_node	*ast;
	char		*quote_cleaned;
	char		*expanded_input;

	(void)argc;
	(void)argv;
	shell.env = envp;
	shell.debug = true;
	setup_signals();
	while (1)
	{
		input = readline("Born2Exec$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		quote_cleaned = clean_quotes(input);
		if (!quote_cleaned)
		{
			memory_free(input);
			continue ;
		}
		expanded_input = expand_variables(quote_cleaned, shell.env);
		memory_free(quote_cleaned);
		tokens = lexer(expanded_input);
		ast = parse_tokens(tokens);
		if (shell.debug)
		{
			print_token_debug(tokens);
			printf("--------------------------------------------------\n");
			print_ast_debug(ast);
		}
		execute_ast(ast, &shell);
		memory_free(tokens);
		memory_free(ast);
		memory_free(expanded_input);
		free(input);
	}
	rl_cleanup_after_signal();
	rl_clear_history();
	memory_cleanup();
	return (0);
}

// TO DO : env memory checking hsamir
// ADD Input to memory list
// TO DO echo should print input if '' instead of "" (REWRITE WHOLE QUOTE HANDLING)
// TO DO export should not change value if there is no equal sign (=) ex: export hi= (should not change) export hi (should not change) export hi="val" $hi = val
// TO DO tokenize input before expander
// SYNTAX CONTROL
