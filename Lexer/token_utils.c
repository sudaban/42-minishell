/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:26 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 03:01:57 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	handle_quote_state(const char *input,
	int i, char *quote, t_shell *shell)
{
	if ((input[i] == '\'' || input[i] == '"') && *quote == 0)
	{
		if (input[i] == '\'')
			shell->should_expand = false;
		*quote = input[i];
		return (1);
	}
	else if (input[i] == *quote)
	{
		*quote = 0;
		return (2);
	}
	return (0);
}

char	*clean_quotes(const char *input, t_shell *shell)
{
	int		i;
	int		j;
	char	quote;
	char	*result;
	int		action;

	result = memory_malloc(ft_strlen(input) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (input[i])
	{
		action = handle_quote_state(input, i, &quote, shell);
		if (action == 1 || action == 2)
			i++;
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
