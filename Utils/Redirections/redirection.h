/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:51:57 by itaskira          #+#    #+#             */
/*   Updated: 2025/06/18 15:52:00 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../../Parser/parser.h"
# include <fcntl.h>
# include <unistd.h>

int	handle_redirections(t_redirection *redir);

#endif
