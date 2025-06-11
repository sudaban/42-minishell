/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:31:10 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/11 17:24:54 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include "Signal/signal.h"
#include "minishell.h"
#include "Lexer/lexer.h"
#include "Parser/parser.h"
#include "Built-In/Exit/exit.h"
#include "Built-In/Pwd/pwd.h"
#include "Built-In/Echo/echo.h"
#include "Built-In/Cd/cd.h"
#include "Built-In/Env/env.h"
#include "Built-In/Export/export.h"
#include "Built-In/Unset/unset.h"
#include "Libft/libft.h"
#include "Utils/Memory/memory.h"

static void	execute_command(char **args, t_shell *shell)
{
    if (strcmp(args[0], "exit") == 0)
        builtin_exit(args);
    else if (strcmp(args[0], "pwd") == 0)
        builtin_pwd(args);
    else if (ft_strncmp(args[0], "echo", 5) == 0)
        builtin_echo(args);
    else if (ft_strncmp(args[0], "cd", 3) == 0)
        builtin_cd(args);
    else if (ft_strncmp(args[0], "env", 4) == 0)
        builtin_env(shell->env);
    else if (ft_strncmp(args[0], "export", 7) == 0)
        builtin_export(args, shell);
    else if (ft_strncmp(args[0], "unset", 6) == 0)
        builtin_unset(args, shell);
    else
        exec_external(args, shell->env);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_shell shell;
    char *input;
    t_token *tokens;
    char *args[100];
    int i;

    shell.env = envp;
    shell.debug = true;

    setup_signals();

    while (1)
    {
        input = readline("Born2Exec$ "); // Add to memory list
        if (!input)
        {
            printf("exit\n");
            break;
        }

        if (*input)
            add_history(input);

        char *quote_cleaned = clean_quotes(input);
        if (!quote_cleaned)
        {
            memory_free(input);
            continue;
        }

        char *expanded_input = expand_variables(quote_cleaned, shell.env);
        memory_free(quote_cleaned);

        tokens = lexer(expanded_input);
        if (shell.debug == true)
            print_token_debug(tokens);

        i = 0;
        char *token = strtok(expanded_input, " ");
        while (token)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0])
            execute_command(args, &shell);

        memory_free(tokens);
        memory_free(expanded_input);
        free(input);
    }
    rl_cleanup_after_signal();
    rl_clear_history();
    memory_cleanup();

    // TO DO : env memory checking hsamir
    // ADD Input to memory list
    return 0;
}
