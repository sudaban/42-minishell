/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:35:43 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 06:01:59 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "../Utils/Redirections/redirection.h"
#include "parser.h"
#include <stdio.h>

t_ast_node	*create_node(void)
{
	t_ast_node	*node;

	node = memory_malloc(sizeof(t_ast_node));
	node->args = NULL;
	node->redirections = NULL;
	node->next_pipe = NULL;
	return (node);
}

t_ast_node	*parse_tokens(t_token *token, t_shell *shell)
{
	t_ast_node	*head;
	t_ast_node	*current;

	head = NULL;
	current = NULL;
	while (token && token->type != T_EOF)
	{
		if (!current)
		{
			current = create_node();
			if (!head)
				head = current;
		}
		if (token->type == T_WORD || token->type == T_ENV_VAR
			|| token->type == T_DOUBLE_QUOTE || token->type == T_SINGLE_QUOTE)
			handle_word_token(current, token, shell);
		else if (token->type == 4 || token->type == 5 || token->type == 6)
			handle_redirection_token(current, &token, shell);
		else if (token->type == T_HEREDOC)
			handle_redirection_token(current, &token, shell);
		else if (token->type == T_PIPE)
			handle_pipe_token(&current);
		token = token->next;
	}
	return (head);
}

void	print_ast_debug(t_ast_node *ast)
{
	int				i;
	t_redirection	*redir;

	while (ast)
	{
		printf("Command:\n");
		i = 0;
		while (ast->args && ast->args[i])
		{
			printf("  Arg[%d]: %s\n", i, ast->args[i]);
			i++;
		}
		redir = ast->redirections;
		while (redir)
		{
			printf("  Redirection: %d -> %s\n", redir->type, redir->filename);
			redir = redir->next;
		}
		ast = ast->next_pipe;
		if (ast)
			printf("  |\n");
	}
}
