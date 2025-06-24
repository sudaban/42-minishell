/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 03:10:00 by itaskira          #+#    #+#             */
/*   Updated: 2025/06/24 02:57:11 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../Signal/signal.h"
#include "../../Utils/Memory/memory.h"
#include "../../minishell.h"
#include "../Status/status.h"
#include "redirection.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	process_heredoc_line(char *line, int fd, t_shell *shell,
		bool expand)
{
	char	*expanded;

	if (expand)
		expanded = expand_variables(line, shell);
	else
		expanded = ft_strdup(line);
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(line);
	memory_free(expanded);
}

static int	setup_heredoc_pipe(void)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	set_signal_handler(2);
	return (pipefd[1]);
}

static int	read_heredoc_lines(int write_fd, const char *delimiter, bool expand,
		t_shell *shell)
{
	char	*line;
	int		read_fd;

	read_fd = write_fd - 1;
	while (1)
	{
		g_signal = 1;
		line = readline("> ");
		if (!line || get_last_exit_status() == 130)
		{
			if (line)
				free(line);
			close(write_fd);
			close(read_fd);
			return (-1);
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, write_fd, shell, expand);
	}
	close(write_fd);
	return (read_fd);
}

int	handle_heredoc(const char *delimiter, bool expand, t_shell *shell)
{
	int	write_fd;
	int	read_fd;

	write_fd = setup_heredoc_pipe();
	if (write_fd == -1)
		return (-1);
	read_fd = read_heredoc_lines(write_fd, delimiter, expand, shell);
	return (read_fd);
}
