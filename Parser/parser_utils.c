/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 02:24:32 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:29:59 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "../Utils/Redirections/redirection.h"

void	add_arg(char ***args, char *value)
{
	int		count;
	char	**new_args;

	if (!*args)
	{
		*args = memory_malloc(sizeof(char *) * 2);
		(*args)[0] = ft_strdup(value);
		(*args)[1] = NULL;
		return ;
	}
	count = 0;
	while ((*args)[count])
		count++;
	new_args = memory_malloc(sizeof(char *) * (count + 2));
	count = 0;
	while ((*args)[count])
	{
		new_args[count] = (*args)[count];
		count++;
	}
	new_args[count] = ft_strdup(value);
	new_args[count + 1] = NULL;
	*args = new_args;
}

void	add_redirection(t_redirection **list, t_token *token)
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

t_ast_node	*create_node(void)
{
	t_ast_node	*node;

	node = memory_malloc(sizeof(t_ast_node));
	node->args = NULL;
	node->redirections = NULL;
	node->next_pipe = NULL;
	return (node);
}
