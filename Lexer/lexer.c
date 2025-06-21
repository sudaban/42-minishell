/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:53:04 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/21 13:52:38 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include <stdio.h>
#include <stdlib.h>

static t_token *create_token(t_token_type type, const char *value)
{
    t_token *new_token = memory_malloc(sizeof(t_token));
    if (!new_token)
        return NULL;
    new_token->type = type;
    new_token->value = ft_strdup(value);
    new_token->next = NULL;
    return new_token;
}

static void add_token(t_token **head, t_token *new_token)
{
    if (!*head)
    {
        *head = new_token;
    }
    else
    {
        t_token *current = *head;
        while (current->next)
            current = current->next;
        current->next = new_token;
    }
}

t_token	*lexer(const char *input)
{
	t_token	*tokens = NULL;
	int		i = 0;
	int		start;
	char	quote;

	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			start = i;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
			{
				if (quote == '\'')
					add_token(&tokens, create_token(T_SINGLE_QUOTE, ft_substr(input, start, i - start)));
				else
					add_token(&tokens, create_token(T_DOUBLE_QUOTE, ft_substr(input, start, i - start)));
				i++; // closing quote
			}
			else
			{
				// unclosed quote, treat rest as word including opening quote
				add_token(&tokens, create_token(T_WORD, ft_substr(input, start - 1, i - start + 1)));
			}
		}
		else if (input[i] == '|')
		{
			if (input[i + 1] == '|')
			{
				add_token(&tokens, create_token(T_OR, "||"));
				i += 2;
			}
			else
				add_token(&tokens, create_token(T_PIPE, "|")), i++;
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_token(&tokens, create_token(T_HEREDOC, "<<"));
				i += 2;
			}
			else
				add_token(&tokens, create_token(T_REDIRECT_IN, "<")), i++;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_token(&tokens, create_token(T_APPEND_OUT, ">>"));
				i += 2;
			}
			else
				add_token(&tokens, create_token(T_REDIRECT_OUT, ">")), i++;
		}
		else if (input[i] == '$')
		{
			i++;
			start = i;
			while (ft_isalnum(input[i]) || input[i] == '_')
				i++;
			if (i > start)
				add_token(&tokens, create_token(T_ENV_VAR, ft_substr(input, start - 1, start)));
			else
				add_token(&tokens, create_token(T_WORD, "$"));
		}
		else if (input[i] == '&')
		{
			if (input[i + 1] == '&')
			{
				add_token(&tokens, create_token(T_AND, "&&"));
				i += 2;
			}
			else
				add_token(&tokens, create_token(T_AMPERSAND, "&")), i++;
		}
		else
		{
			start = i;
			while (input[i] && !ft_isspace(input[i]) &&
				input[i] != '"' && input[i] != '\'' &&
				input[i] != '|' && input[i] != '<' &&
				input[i] != '>' && input[i] != '$' &&
				input[i] != '&')
				i++;
			add_token(&tokens, create_token(T_WORD, ft_substr(input, start, i - start)));
		}
	}
	add_token(&tokens, create_token(T_EOF, ft_strdup("EOF")));
	return (tokens);
}



void print_token_debug(t_token *tokens)
{
    const char *token_type_str[] = {
        "T_WORD",
        "T_SINGLE_QUOTE",
        "T_DOUBLE_QUOTE",
        "T_PIPE",
        "T_REDIRECT_IN",
        "T_REDIRECT_OUT",
        "T_APPEND_OUT",
        "T_HEREDOC",
        "T_ENV_VAR",
        "T_EXIT_STATUS",
        "T_NEWLINE",
        "T_EOF",
        "T_OR",
        "T_AND",
        "T_AMPERSAND"
    };

    while (tokens)
    {
        const char *token_type = "UNKNOWN";
        if (tokens->type >= 0 && tokens->type <= T_AMPERSAND)
            token_type = token_type_str[tokens->type];
        printf("Token: '%s', Type: %s\n", tokens->value, token_type);
        tokens = tokens->next;
    }
}