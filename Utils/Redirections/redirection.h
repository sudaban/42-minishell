/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:02 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:57:09 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../../Parser/parser.h"
# include "../../minishell.h"
# include <fcntl.h>
# include <unistd.h>

int		handle_redirections(t_redirection *redir, t_shell *shell);
void	add_redir_quoted(t_redirection **list, t_token *token, bool quoted);
int		handle_heredoc(const char *delimiter, bool expand, t_shell *shell);

#endif
