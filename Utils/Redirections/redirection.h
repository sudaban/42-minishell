/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:02 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/20 15:04:20 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../../Parser/parser.h"
# include <fcntl.h>
# include <unistd.h>
# include "../../minishell.h"
int	handle_redirections(t_redirection *redir, t_shell *shell);

#endif
