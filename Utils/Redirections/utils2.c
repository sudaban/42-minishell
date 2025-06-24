/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 05:12:24 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:13:30 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	open_file_by_type(t_redirection *redir)
{
	if (redir->type == T_REDIRECT_IN)
		return (open(redir->filename, O_RDONLY));
	if (redir->type == T_REDIRECT_OUT)
		return (open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (redir->type == T_APPEND_OUT)
		return (open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

int	apply_fd_redirect(int fd, int type)
{
	if (type == T_REDIRECT_IN || type == T_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
