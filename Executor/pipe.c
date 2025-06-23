/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:27:43 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:07:00 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Utils/Memory/memory.h"
#include "../Utils/Redirections/redirection.h"
#include "../Utils/Status/status.h"
#include "executor.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../Signal/signal.h"

void	execute_pipeline(t_ast_node *ast, t_shell *shell)
{
	int			pipefd[2];
	int			input_fd;
	int			pid;
	int			status;
	t_ast_node	*current;
	int			has_next;

	input_fd = dup(STDIN_FILENO);
	current = ast;
	while (current)
	{
		has_next = (current->next_pipe != NULL);
		if (has_next && pipe(pipefd) == -1)
		{
			perror("pipe");
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			if (input_fd != STDIN_FILENO)
			{
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			if (has_next)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			if (current->redirections)
			{
				if (handle_redirections(current->redirections, shell) != 0)
					exit(1);
			}
			execute_command(current->args, shell);
			exit(get_last_exit_status());
		}
		else if (pid < 0)
		{
			perror("fork");
			return ;
		}
		else
		{
			set_signal_handler(1);
		}
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (has_next)
		{
			close(pipefd[1]);
			input_fd = pipefd[0];
		}
		current = current->next_pipe;
	}
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));

	set_signal_handler(0);
}

