/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:26 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:22:49 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*clean_quotes(const char *input, t_shell *shell)
{
	int		i;
	int		j;
	char	quote;
	char	*result;

	result = memory_malloc(ft_strlen(input) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && quote == 0)
		{
			if (input[i] == '\'')
				shell->should_expand = false;
			quote = input[i++];
		}
		else if (input[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
		{
			result[j++] = input[i++];
		}
	}
	result[j] = '\0';
	return (result);
}

void	adjust_should_expand(const char *input, t_shell *shell)
{
	int		single_quote_count;
	size_t	i;

	i = 0;
	single_quote_count = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			single_quote_count++;
		i++;
	}
	if (single_quote_count >= 2 && single_quote_count % 2 == 0)
		shell->should_expand = false;
	else
		shell->should_expand = true;
}
