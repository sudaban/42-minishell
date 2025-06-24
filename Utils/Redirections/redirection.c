/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:04 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:57:05 by itaskira         ###   ########.fr       */
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

void	add_redir_quoted(t_redirection **list, t_token *token, bool quoted)
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

static int	open_redirection_file(t_redirection *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == T_REDIRECT_IN)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == T_REDIRECT_OUT)
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == T_APPEND_OUT)
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		set_exit_status(1);
	}
	return (fd);
}

static void	apply_redirection(int fd, t_redirection *redir)
{
	if (redir->type == T_REDIRECT_IN || redir->type == T_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	handle_redirections(t_redirection *redir, t_shell *shell)
{
	int	fd;

	while (redir)
	{
		if (redir->type == T_HEREDOC)
		{
			fd = handle_heredoc(redir->filename, shell->should_expand, shell);
			if (fd == -1)
				return (1);
		}
		else
		{
			fd = open_redirection_file(redir);
			if (fd == -1)
				return (1);
		}
		apply_redirection(fd, redir);
		redir = redir->next;
	}
	return (0);
}
