/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:16:09 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:28:41 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:16:09 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:50:03 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "../Libft/libft.h"
#include "signal.h"
#include "../minishell.h"

int	g_signal = 0;

static int	randomfuncc(void)
{
	return (0);
}

void	set_signal_handler(int type)
{
	g_signal = 0;
	if (type == 0)
	{
		rl_event_hook = NULL;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_prompt);
	}
	else if (type == 1)
	{
		rl_event_hook = NULL;
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, handle_exec);
	}
	else if (type == 2)
	{
		rl_event_hook = randomfuncc;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_heredoc_sig);
	}
}
