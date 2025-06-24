/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:04 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:13:18 by sdaban           ###   ########.fr       */
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

void	add_redirection_with_quoted(t_redirection **list, t_token *token,
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
	new_redir->filename = get_filename_with_quotes(token, quoted);
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

int	handle_heredoc(const char *delimiter, bool expand, t_shell *shell)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	set_signal_handler(2);
	if (read_heredoc_lines(pipefd, delimiter, expand, shell) == -1)
		return (-1);
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
			fd = handle_heredoc(redir->filename, shell->should_expand, shell);
		else
			fd = open_file_by_type(redir);
		if (fd == -1)
		{
			perror(redir->filename);
			set_exit_status(1);
			return (1);
		}
		apply_fd_redirect(fd, redir->type);
		redir = redir->next;
	}
	return (0);
}
