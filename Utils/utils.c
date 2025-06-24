/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:35:12 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:37:56 by sdaban           ###   ########.fr       */
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
	char	*result;
	char	var[256];
	char	*val;
	int		i;
	int		j;
	int		k;

	if (!shell->should_expand)
		return (ft_strdup(input));
	result = memory_malloc(calc_len(input, shell->env) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '?')
			{
				val = ft_itoa(get_last_exit_status());
				copy_var_value(result, &j, val);
				memory_free(val);
				i++;
			}
			else
			{
				k = 0;
				while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
					var[k++] = input[i++];
				var[k] = '\0';
				val = get_env_value(var, shell->env);
				if (val)
					copy_var_value(result, &j, val);
			}
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
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
static char	*get_cmd_path_and_check(char *cmd, char **env)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd, env);
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", cmd);
		exit(127);
	}
	return (cmd_path);
}

static void	exec_child_process(char *cmd, char **args, char **env)
{
	char	*cmd_path;

	cmd_path = get_cmd_path_and_check(cmd, env);
	execve(cmd_path, args, env);
	perror("execve");
	exit(1);
}

static void	exec_parent_process(pid_t pid, int *status)
{
	set_signal_handler(1);
	waitpid(pid, status, 0);
	set_signal_handler(0);
	if (WIFEXITED(*status))
		set_exit_status(WEXITSTATUS(*status));
	else
		set_exit_status(1);
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
