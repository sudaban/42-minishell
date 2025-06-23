/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:51:26 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:02:31 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "../minishell.h"
#include <stdio.h>

char *clean_quotes(const char *input, t_shell *shell)
{
    int     i;
    int     j;
    char    quote;
    char    *result;

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

