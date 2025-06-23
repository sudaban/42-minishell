/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:41:40 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:42:23 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Built-In/Cd/cd.h"
#include "../Built-In/Echo/echo.h"
#include "../Built-In/Env/env.h"
#include "../Built-In/Exit/exit.h"
#include "../Built-In/Export/export.h"
#include "../Built-In/Pwd/pwd.h"
#include "../Built-In/Unset/unset.h"
#include "../Libft/libft.h"
#include "../Utils/Redirections/redirection.h"
#include "../Utils/Status/status.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	execute_command(char **args, t_shell *shell)
{
	if (ft_strncmp(args[0], "exit", 5) == 0)
		builtin_exit(args);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
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

void	execute_ast(t_ast_node *ast, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;

	if (!ast)
		return ;
	if (ast->next_pipe)
	{
		execute_pipeline(ast, shell);
	}
	else
	{
		stdin_backup = dup(0);
		stdout_backup = dup(1);
		if (ast->redirections)
		{
			if (handle_redirections(ast->redirections, shell) != 0)
			{
				set_exit_status(1);
				dup2(stdin_backup, 0);
				dup2(stdout_backup, 1);
				close(stdin_backup);
				close(stdout_backup);
				return ;
			}
		}
		if (!ast->args || !ast->args[0])
		{
			dup2(stdin_backup, 0);
			dup2(stdout_backup, 1);
			close(stdin_backup);
			close(stdout_backup);
			set_exit_status(0);
			return ;
		}
		execute_command(ast->args, shell);
		dup2(stdin_backup, 0);
		dup2(stdout_backup, 1);
		close(stdin_backup);
		close(stdout_backup);
	}
}
