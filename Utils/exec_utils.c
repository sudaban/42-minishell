/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 03:30:00 by itaskira          #+#    #+#             */
/*   Updated: 2025/06/24 03:05:13 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Signal/signal.h"
#include "../Utils/Status/status.h"
#include "../minishell.h"
#include "Memory/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char	*find_executable(char *cmd, char **env)
{
	char	*path;
	char	**dirs;
	char	full_path[512];
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
			return (ft_strdup(full_path));
		}
		i++;
	}
	return (NULL);
}

static char	*get_cmd_path(char *cmd, char **env)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (find_executable(cmd, env));
}

static void	handle_child_process(char **args, char **env)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(args[0], env);
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		exit(127);
	}
	execve(cmd_path, args, env);
	perror("execve");
	exit(1);
}

static void	handle_parent_process(pid_t pid)
{
	int	status;

	set_signal_handler(1);
	waitpid(pid, &status, 0);
	set_signal_handler(0);
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	else
		set_exit_status(1);
}

void	exec_external(char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		handle_child_process(args, env);
	else if (pid > 0)
		handle_parent_process(pid);
	else
	{
		perror("fork");
		set_exit_status(1);
	}
}
