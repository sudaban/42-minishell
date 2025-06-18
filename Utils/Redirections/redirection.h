/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:46:02 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 14:19:14 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../../Parser/parser.h"
# include <fcntl.h>
# include <unistd.h>

void	handle_redirections(t_redirection *redir);

#endif
