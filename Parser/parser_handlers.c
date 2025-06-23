/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 02:32:39 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:32:43 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../Utils/Memory/memory.h"

bool	is_word_token(t_token *token)
{
	return (token->type == T_WORD || token->type == T_ENV_VAR
		|| token->type == T_DOUBLE_QUOTE || token->type == T_SINGLE_QUOTE);
}

bool	is_redirection_token(t_token *token)
{
	return (token->type == T_REDIRECT_IN || token->type == T_REDIRECT_OUT
		|| token->type == T_APPEND_OUT);
}

void	init_node(t_ast_node **head, t_ast_node **current)
{
	*current = create_node();
	if (!*head)
		*head = *current;
}

void	handle_redirect_token(t_token **token, t_ast_node *current)
{
	if ((*token)->next)
		add_redirection(&current->redirections, *token);
	*token = (*token)->next;
}

void	handle_pipe_token(t_ast_node **current)
{
	(*current)->next_pipe = create_node();
	*current = (*current)->next_pipe;
}
