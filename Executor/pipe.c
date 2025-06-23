/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:27:43 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:43:16 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Signal/signal.h"
#include "../Utils/Memory/memory.h"
#include "../Utils/Redirections/redirection.h"
#include "../Utils/Status/status.h"
#include "executor.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	handle_pipe_iteration(t_ast_node *current, int *input_fd,
		t_shell *shell, int *last_pid)
{
	t_pipe_data	data;
	int			pid;

	prepare_pipe_data(&data, current, input_fd, shell);
	if (data.has_next == -1)
		return ;
	pid = fork();
	if (pid == 0)
		execute_child_process(&data);
	else if (pid < 0)
		perror("fork");
	else
		*last_pid = pid;
	cleanup_pipe_fds(&data, input_fd);
}

void	execute_pipeline(t_ast_node *ast, t_shell *shell)
{
	int			input_fd;
	int			status;
	t_ast_node	*current;
	int			last_pid;

	input_fd = dup(STDIN_FILENO);
	current = ast;
	last_pid = -1;
	set_signal_handler(1);
	while (current)
	{
		handle_pipe_iteration(current, &input_fd, shell, &last_pid);
		current = current->next_pipe;
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	set_signal_handler(0);
}
