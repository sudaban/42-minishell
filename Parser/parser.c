/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:35:43 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 14:28:19 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "parser.h"
#include <stdio.h>

static void	add_arg(char ***args, char *value)
{
	int		i;
	char	**new_args;

	if (!*args)
	{
		*args = memory_malloc(sizeof(char *) * 2);
		(*args)[0] = ft_strdup(value);
		(*args)[1] = NULL;
		return ;
	}
	for (i = 0; (*args)[i]; i++)
		;
	new_args = memory_malloc(sizeof(char *) * (i + 2));
	for (i = 0; (*args)[i]; i++)
		new_args[i] = (*args)[i];
	new_args[i] = ft_strdup(value);
	new_args[i + 1] = NULL;
	*args = new_args;
}

static void	add_redirection(t_redirection **list, t_token *token)
{
	t_redirection	*new;
	t_redirection	*tmp;

	new = memory_malloc(sizeof(t_redirection));
	new->type = token->type;
	new->filename = ft_strdup(token->next->value);
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_ast_node	*create_node(void)
{
	t_ast_node	*node;

	node = memory_malloc(sizeof(t_ast_node));
	node->args = NULL;
	node->redirections = NULL;
	node->next_pipe = NULL;
	return (node);
}

t_ast_node	*parse_tokens(t_token *token)
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
			add_arg(&current->args, token->value);
		else if (token->type == T_REDIRECT_IN || token->type == T_REDIRECT_OUT
			|| token->type == T_APPEND_OUT || token->type == T_HEREDOC)
		{
			if (token->next)
				add_redirection(&current->redirections, token);
			token = token->next;
		}
		else if (token->type == T_PIPE)
		{
			current->next_pipe = create_node();
			current = current->next_pipe;
		}
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
		for (i = 0; ast->args && ast->args[i]; i++)
			printf("  Arg[%d]: %s\n", i, ast->args[i]);
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
