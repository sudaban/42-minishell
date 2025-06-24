/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 00:47:54 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:51:12 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "lexer.h"
#include <stdlib.h>

static size_t	count_words(const char *str, char delimiter)
{
	size_t	word_count;
	int		i;

	word_count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == delimiter)
			i++;
		if (!str[i])
			break ;
		word_count++;
		i += skip_word(&str[i], delimiter);
	}
	return (word_count);
}

static void	free_all_memory(char **word_list, int index)
{
	while (index >= 0)
		free(word_list[index--]);
	free(word_list);
}

static char	*extract_word(const char *str, char delimiter)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = 0;
	while (str[len])
	{
		if (!quote && (str[len] == '\'' || str[len] == '"'))
			quote = str[len];
		else if (quote && str[len] == quote)
			quote = 0;
		else if (!quote && str[len] == delimiter)
			break ;
		len++;
	}
	return (ft_substr(str, 0, len));
}

static int	fill_word_list(char **word_list, const char *str, char delimiter)
{
	int		index;
	char	*word;

	index = 0;
	while (*str)
	{
		while (*str == delimiter)
			str++;
		if (!*str)
			break ;
		word = extract_word(str, delimiter);
		if (!word)
		{
			free_all_memory(word_list, index - 1);
			return (0);
		}
		word_list[index++] = word;
		str += ft_strlen(word);
	}
	word_list[index] = NULL;
	return (1);
}

char	**lexer_split(char const *s, char c, t_shell *shell)
{
	char	**lst;
	char	*expanded;

	expanded = NULL;
	if (!s)
		return (NULL);
	if (shell->should_expand)
		expanded = expand_variables(s, shell);
	else
		expanded = ft_strdup(s);
	if (!expanded)
		return (NULL);
	lst = (char **)memory_malloc((count_words(expanded, c) + 1)
			* sizeof(char *));
	if (!lst || !fill_word_list(lst, expanded, c))
	{
		memory_free(expanded);
		return (NULL);
	}
	memory_free(expanded);
	return (lst);
}
