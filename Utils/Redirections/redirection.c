/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:04 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 14:24:58 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <stdio.h>

void	handle_redirections(t_redirection *redir)
{
	int	fd;

	while (redir)
	{
		fd = -1;
		if (redir->type == T_REDIRECT_IN)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == T_REDIRECT_OUT)
			fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redir->type == T_APPEND_OUT)
			fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (redir->type == T_HEREDOC)
		{
			redir = redir->next;
			continue ;
		}
		if (fd == -1)
		{
			perror("redirection");
			return ;
		}
		if (redir->type == T_REDIRECT_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}
