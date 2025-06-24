/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 04:58:58 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:38:56 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "../Utils/Redirections/redirection.h"
#include "parser.h"

t_ast_node	*create_node(void)
{
	t_ast_node	*node;

	node = memory_malloc(sizeof(t_ast_node));
	node->args = NULL;
	node->redirections = NULL;
	node->next_pipe = NULL;
	return (node);
}

t_ast_node	*prepare_current_node(t_ast_node *current, t_ast_node **head)
{
	if (!current)
	{
		current = create_node();
		if (!*head)
			*head = current;
	}
	return (current);
}

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

void	handle_word_token(t_ast_node *current, t_token *token, t_shell *shell)
{
	char	*processed;
	char	*expanded;

	shell->should_expand = (token->type != T_SINGLE_QUOTE);
	processed = clean_quotes(token->value, shell);
	if (shell->should_expand)
	{
		expanded = expand_variables(processed, shell);
		add_arg(&current->args, expanded);
		memory_free(expanded);
	}
	else
		add_arg(&current->args, processed);
	memory_free(processed);
}
