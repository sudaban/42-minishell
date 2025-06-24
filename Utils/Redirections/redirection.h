/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:02 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:15:01 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../../Parser/parser.h"
# include "../../minishell.h"
# include <fcntl.h>
# include <unistd.h>

int		handle_redirections(t_redirection *redir, t_shell *shell);
void	add_redirection_with_quoted(t_redirection **list, t_token *token,
			bool quoted);
int		open_file_by_type(t_redirection *redir);
int		apply_fd_redirect(int fd, int type);
char	*get_filename_with_quotes(t_token *token, bool quoted);
int		handle_heredoc(const char *delimiter, bool expand, t_shell *shell);
int		check_heredoc_interrupt(char *line, int *pipefd);
void	write_heredoc_line(int fd, char *line);
int		read_heredoc_lines(int *pipefd, const char *delimiter,
			bool expand, t_shell *shell);
#endif
