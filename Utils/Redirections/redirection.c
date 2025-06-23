/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:04 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:26:31 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
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
#include "../../Signal/signal.h"

void	add_redir_quoted(t_redirection **list, t_token *token,
		bool quoted)
{
	t_redirection	*new_redir;
	t_redirection	*tmp;

	tmp = *list;
	new_redir = memory_malloc(sizeof(t_redirection));
	if (!new_redir)
		return ;
	new_redir->type = token->type;
	new_redir->quoted = quoted;
	if (quoted)
		new_redir->filename = ft_substr(token->next->value, 1,
				ft_strlen(token->next->value) - 2);
	else
		new_redir->filename = ft_strdup(token->next->value);
	new_redir->next = NULL;
	if (!*list)
		*list = new_redir;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

static int	handle_heredoc(const char *delimiter, bool expand, t_shell *shell)
{
	int		pipefd[2];
	char	*line;
	char	*expanded;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	set_signal_handler(2);
	while (1)
	{
		g_signal = 1;
		line = readline("> ");
		if (!line || get_last_exit_status() == 130)
		{
			if (line)
				free(line);
			close(pipefd[1]);
			close(pipefd[0]);
			return (-1); // heredoc aborted
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
			expanded = expand_variables(line, shell);
		else
			expanded = ft_strdup(line);
		write(pipefd[1], expanded, ft_strlen(expanded));
		write(pipefd[1], "\n", 1);
		free(line);
		memory_free(expanded);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	handle_redirections(t_redirection *redir, t_shell *shell)
{
	int	fd;

	while (redir)
	{
		fd = -1;
		if (redir->type == T_HEREDOC)
		{
			fd = handle_heredoc(redir->filename, shell->should_expand, shell);
			if (fd == -1)
				return (1);
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
