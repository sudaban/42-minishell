/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 03:00:00 by itaskira          #+#    #+#             */
/*   Updated: 2025/06/24 02:57:12 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Utils/Redirections/redirection.h"
#include "../Utils/Status/status.h"
#include "executor.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	setup_input_output(t_pipe_data *data)
{
	if (data->input_fd != STDIN_FILENO)
	{
		dup2(data->input_fd, STDIN_FILENO);
		close(data->input_fd);
	}
	if (data->has_next)
	{
		dup2(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
}

void	execute_child_process(t_pipe_data *data)
{
	setup_input_output(data);
	if (data->current->redirections)
	{
		if (handle_redirections(data->current->redirections, data->shell) != 0)
			exit(1);
	}
	execute_command(data->current->args, data->shell);
	exit(get_last_exit_status());
}

void	prepare_pipe_data(t_pipe_data *data, t_ast_node *current, int *input_fd,
		t_shell *shell)
{
	data->input_fd = *input_fd;
	data->current = current;
	data->shell = shell;
	data->has_next = (current->next_pipe != NULL);
	if (data->has_next && pipe(data->pipefd) == -1)
	{
		perror("pipe");
		data->has_next = -1;
	}
}

void	cleanup_pipe_fds(t_pipe_data *data, int *input_fd)
{
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (data->has_next > 0)
	{
		close(data->pipefd[1]);
		*input_fd = data->pipefd[0];
	}
}
