/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:27:43 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 12:49:51 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include "executor.h"
#include "../Utils/Memory/memory.h"
#include "../Utils/Redirections/redirection.h"
#include "../Utils/Status/status.h"
#include <stdlib.h>

void	execute_pipeline(t_ast_node *ast, t_shell *shell)
{
	int		pipefd[2];
	int		input_fd = dup(STDIN_FILENO);
	int		pid;
	int		status;
	t_ast_node *current = ast;

	while (current)
	{
		int		has_next = (current->next_pipe != NULL);

		if (has_next && pipe(pipefd) == -1)
		{
			perror("pipe");
			return ;
		}

		pid = fork();
		if (pid == 0)
		{
			// Input redirection (from previous pipe)
			if (input_fd != STDIN_FILENO)
			{
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}

			// Output redirection (to next pipe)
			if (has_next)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}

			if (current->redirections)
			{
				if (handle_redirections(current->redirections) != 0)
					exit(1);
			}

			execute_command(current->args, shell);
			memory_cleanup();
			exit(get_last_exit_status());
		}
		else if (pid < 0)
		{
			perror("fork");
			return ;
		}

		// Parent: prepare for next iteration
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
}
