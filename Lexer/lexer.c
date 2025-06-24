/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:53:04 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 04:52:41 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*new_token;

	new_token = memory_malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	return (new_token);
}

static void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	current = *head;
	if (!*head)
	{
		*head = new_token;
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

t_token_type	get_token_type(const char *value)
{
	if (strcmp(value, "|") == 0)
		return (T_PIPE);
	else if (strcmp(value, "<") == 0)
		return (T_REDIRECT_IN);
	else if (strcmp(value, ">") == 0)
		return (T_REDIRECT_OUT);
	else if (strcmp(value, ">>") == 0)
		return (T_APPEND_OUT);
	else if (strcmp(value, "<<") == 0)
		return (T_HEREDOC);
	else if (strcmp(value, "&") == 0)
		return (T_AMPERSAND);
	else if (strcmp(value, "||") == 0)
		return (T_OR);
	else if (strcmp(value, "&&") == 0)
		return (T_AND);
	else if (value[0] == '\'' && value[strlen(value) - 1] == '\'')
		return (T_SINGLE_QUOTE);
	else if (value[0] == '\"' && value[strlen(value) - 1] == '\"')
		return (T_DOUBLE_QUOTE);
	else if (value[0] == '$')
		return (T_ENV_VAR);
	else if (strcmp(value, "\n") == 0)
		return (T_NEWLINE);
	else if (strcmp(value, "") == 0)
		return (T_EOF);
	else
		return (T_WORD);
}

t_token	*lexer(char **input)
{
	t_token			*tokens;
	t_token			*new_token;
	int				i;
	t_token_type	type;

	tokens = NULL;
	i = 0;
	while (input[i] != NULL)
	{
		type = get_token_type(input[i]);
		new_token = create_token(type, input[i]);
		add_token(&tokens, new_token);
		i++;
	}
	return (tokens);
}

void	print_token_debug(t_token *tokens)
{
	const char	*token_type_str[] = {"T_WORD", "T_SINGLE_QUOTE",
		"T_DOUBLE_QUOTE", "T_PIPE", "T_REDIRECT_IN", "T_REDIRECT_OUT",
		"T_APPEND_OUT", "T_HEREDOC", "T_ENV_VAR", "T_EXIT_STATUS",
		"T_NEWLINE", "T_EOF", "T_OR", "T_AND", "T_AMPERSAND"};
	const char	*token_type = "UNKNOWN";

	while (tokens)
	{
		if (tokens->type >= 0 && tokens->type <= T_AMPERSAND)
			token_type = token_type_str[tokens->type];
		printf("Token: '%s', Type: %s\n", tokens->value, token_type);
		tokens = tokens->next;
	}
}

void adjust_should_expand(const char *input, t_shell *shell)
{
    int single_quote_count = 0;
    size_t i = 0;

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
