/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 06:12:02 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 06:42:40 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Status/status.h"
#include "../minishell.h"
#include "Memory/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../Signal/signal.h"

char	*get_cmd_path_and_check(char *cmd, char **env)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd, env);
	if (!cmd_path)
	{
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd("", STDERR_FILENO);
		exit(127);
	}
	return (cmd_path);
}

void	exec_child_process(char *cmd, char **args, char **env)
{
	char	*cmd_path;

	cmd_path = get_cmd_path_and_check(cmd, env);
	set_signal_handler(1);
	execve(cmd_path, args, env);
	perror("execve");
	exit(1);
}

void	exec_parent_process(pid_t pid, int *status)
{
	set_signal_handler(1);
	waitpid(pid, status, 0);
	set_signal_handler(0);
	if (WIFEXITED(*status))
		set_exit_status(WEXITSTATUS(*status));
	else
		set_exit_status(1);
}

void	handle_variable_expansion(t_expand_context *ctx)
{
	char	var[256];
	char	*val;
	int		k;

	if (ctx->input[ctx->i] == '?')
	{
		val = ft_itoa(get_last_exit_status());
		if (val)
		{
			copy_var_value(ctx->result, &ctx->j, val);
			memory_free(val);
		}
		ctx->i++;
	}
	else
	{
		k = 0;
		while (ctx->input[ctx->i]
			&& (ft_isalnum(ctx->input[ctx->i]) || ctx->input[ctx->i] == '_'))
			var[k++] = ctx->input[(ctx->i)++];
		var[k] = '\0';
		val = get_env_value(var, ctx->shell->env);
		if (val)
			copy_var_value(ctx->result, &ctx->j, val);
	}
}
