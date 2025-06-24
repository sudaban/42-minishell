/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:41:40 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 06:33:26 by sdaban           ###   ########.fr       */
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

static void	cleanup_fds(int stdin_fd, int stdout_fd)
{
	dup2(stdin_fd, 0);
	dup2(stdout_fd, 1);
	close(stdin_fd);
	close(stdout_fd);
}

static int	setup_and_check_redirections(t_ast_node *ast, t_shell *shell,
		int stdin_fd, int stdout_fd)
{
	if (ast->redirections)
	{
		if (handle_redirections(ast->redirections, shell) != 0)
		{
			set_exit_status(1);
			cleanup_fds(stdin_fd, stdout_fd);
			return (1);
		}
	}
	if (!ast->args || !ast->args[0])
	{
		cleanup_fds(stdin_fd, stdout_fd);
		set_exit_status(0);
		return (1);
	}
	return (0);
}

static void	execute_simple_command(t_ast_node *ast, t_shell *shell)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(0);
	stdout_backup = dup(1);
	if (setup_and_check_redirections(ast, shell, stdin_backup, stdout_backup))
		return ;
	execute_command(ast->args, shell);
	cleanup_fds(stdin_backup, stdout_backup);
}

void	execute_ast(t_ast_node *ast, t_shell *shell)
{
	if (!ast)
		return ;
	if (ast->next_pipe)
		execute_pipeline(ast, shell);
	else
		execute_simple_command(ast, shell);
}
