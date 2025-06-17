/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:02 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/17 13:46:26 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../../Parser/parser.h"
# include <fcntl.h>
# include <unistd.h>

void	handle_redirections(t_redirection *redir);

#endif
