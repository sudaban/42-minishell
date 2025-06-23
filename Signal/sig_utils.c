/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 01:58:01 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:28:37 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../Libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include "../Utils/Status/status.h"

void	handle_prompt(int signal)
{
	g_signal = signal;
	ft_putendl_fd("", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	handle_exit_status(signal + 128, 0, 0);
}

void	handle_sigquit(int signal)
{
	g_signal = signal;
	ft_putendl_fd("quit (core dumped)", 1);
	rl_replace_line("", 0);
	handle_exit_status(signal + 128, 0, 0);
}

void	handle_exec(int signal)
{
	g_signal = signal;
	ft_putendl_fd("", 1);
	handle_exit_status(signal + 128, 0, 0);
}

void	handle_heredoc_sig(int signal)
{
	g_signal = signal;
	rl_replace_line("", 0);
	rl_done = 1;
	handle_exit_status(signal + 128, 0, 0);
}
