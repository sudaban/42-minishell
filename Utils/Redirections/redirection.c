/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:04 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 12:40:12 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../Status/status.h"
#include <stdio.h>

int	handle_redirections(t_redirection *redir)
{
	while (redir)
	{
		int	fd = -1;

		if (redir->type == T_REDIRECT_IN)
			fd = open(redir->filename, O_RDONLY);
		else if (redir->type == T_REDIRECT_OUT)
			fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redir->type == T_APPEND_OUT)
			fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (redir->type == T_HEREDOC)
		{
			// here will be heredoc
			redir = redir->next;
			continue;
		}

		if (fd == -1)
		{
			perror(redir->filename);
			set_exit_status(1);
			return (1);
		}

		if (redir->type == T_REDIRECT_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);

		close(fd);
		redir = redir->next;
	}
	return (0);
}

