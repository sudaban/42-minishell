/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:26 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 14:23:19 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include <stdlib.h>

char	*clean_quotes(const char *input)
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
			quote = input[i++];
		else if (input[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
