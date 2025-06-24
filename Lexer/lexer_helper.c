/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 05:44:22 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:51:17 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../Libft/libft.h"

t_token_type	match_operator(const char *value)
{
	if (ft_strncmp(value, "|", 2) == 0)
		return (T_PIPE);
	if (ft_strncmp(value, "<", 2) == 0)
		return (T_REDIRECT_IN);
	if (ft_strncmp(value, ">", 2) == 0)
		return (T_REDIRECT_OUT);
	if (ft_strncmp(value, ">>", 3) == 0)
		return (T_APPEND_OUT);
	if (ft_strncmp(value, "<<", 3) == 0)
		return (T_HEREDOC);
	if (ft_strncmp(value, "&", 2) == 0)
		return (T_AMPERSAND);
	if (ft_strncmp(value, "||", 3) == 0)
		return (T_OR);
	if (ft_strncmp(value, "&&", 3) == 0)
		return (T_AND);
	return (T_WORD);
}

t_token_type	match_specials(const char *value)
{
	if (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
		return (T_SINGLE_QUOTE);
	if (value[0] == '\"' && value[ft_strlen(value) - 1] == '\"')
		return (T_DOUBLE_QUOTE);
	if (value[0] == '$')
		return (T_ENV_VAR);
	if (ft_strncmp(value, "\n", 2) == 0)
		return (T_NEWLINE);
	if (ft_strncmp(value, "", 1) == 0)
		return (T_EOF);
	return (T_WORD);
}

int	skip_word(const char *str, char delimiter)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else if (!quote && str[i] == delimiter)
			break ;
		i++;
	}
	return (i);
}
