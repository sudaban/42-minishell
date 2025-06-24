/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:37:03 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 06:30:19 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static bool	has_unclosed_quotes(const char *input)
{
	char	quote;

	quote = 0;
	while (*input)
	{
		if ((*input == '\'' || *input == '"'))
		{
			if (quote == 0)
				quote = *input;
			else if (quote == *input)
				quote = 0;
		}
		input++;
	}
	return (quote != 0);
}

static bool	starts_with_pipe(const char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	return (*input == '|');
}

bool	check_syntax(const char *input)
{
	if (has_unclosed_quotes(input))
	{
		ft_putstr_fd("Syntax error: unclosed quote\n", STDERR_FILENO);
		return (false);
	}
	if (starts_with_pipe(input))
	{
		ft_putstr_fd("Syntax error: input cannot start with a pipe\n",
			STDERR_FILENO);
		return (false);
	}
	return (true);
}
