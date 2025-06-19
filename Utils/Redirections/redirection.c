/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:04 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/19 13:56:14 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../Status/status.h"
#include "../../Libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <stdbool.h>
#include "../../minishell.h"

static int	handle_heredoc(const char *delimiter, bool expand, char **env)
{
	int		pipefd[2];
	char	*line;
	char	*expanded;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break;
		}
		if (expand)
			expanded = expand_variables(line, env);
		else
			expanded = ft_strdup(line);
		write(pipefd[1], expanded, ft_strlen(expanded));
		write(pipefd[1], "\n", 1);
		free(line);
		free(expanded);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}


int	handle_redirections(t_redirection *redir, char **env)
{
	int	fd;

	while (redir)
	{
		fd = -1;
		if (redir->type == T_HEREDOC)
		{
			bool quoted = false;
			char *delim = redir->filename;

			if ((delim[0] == '\'' || delim[0] == '"') &&
				delim[ft_strlen(delim) - 1] == delim[0])
			{
				quoted = true;
				delim = ft_substr(delim, 1, ft_strlen(delim) - 2);
			}

			fd = handle_heredoc(delim, !quoted, env);
			if (quoted)
				free(delim);
		}
		else if (redir->type == T_REDIRECT_IN)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == T_REDIRECT_OUT)
			fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redir->type == T_APPEND_OUT)
			fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);

		if (fd == -1)
		{
			perror(redir->filename);
			set_exit_status(1);
			return (1);
		}
		if (redir->type == T_REDIRECT_IN || redir->type == T_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);

		close(fd);
		redir = redir->next;
	}
	return (0);
}
