/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:35:12 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 06:20:14 by sdaban           ###   ########.fr       */
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

char	*get_env_value(const char *key, char **env)
{
	int		i;
	size_t	len;

	if (!key)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*expand_variables(const char *input, t_shell *shell)
{
	t_expand_context	ctx;

	if (!shell->should_expand)
		return (ft_strdup(input));
	ctx.result = memory_malloc(calc_len(input, shell->env) + 1);
	if (!ctx.result)
		return (NULL);
	ctx.input = input;
	ctx.shell = shell;
	ctx.i = 0;
	ctx.j = 0;
	while (input[ctx.i])
	{
		if (input[ctx.i] == '$')
		{
			ctx.i++;
			handle_variable_expansion(&ctx);
		}
		else
			ctx.result[ctx.j++] = input[ctx.i++];
	}
	ctx.result[ctx.j] = '\0';
	return (ctx.result);
}

char	*find_executable(char *cmd, char **env)
{
	char	*path;
	char	**dirs;
	char	full_path[512];
	char	*ret;
	int		i;

	path = get_env_value("PATH", env);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			ret = ft_strdup(full_path);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

void	exec_external(char **args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exec_child_process(args[0], args, env);
	}
	else if (pid > 0)
	{
		exec_parent_process(pid, &status);
	}
	else
	{
		perror("fork");
		set_exit_status(1);
	}
}
