/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:16:14 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:30:40 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

void	set_signal_handler(int type);
void	handle_prompt(int signal);
void	handle_sigquit(int signal);
void	handle_exec(int signal);
void	handle_heredoc_sig(int signal);
#endif
