/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 05:37:52 by itaskira          #+#    #+#             */
/*   Updated: 2025/06/24 05:38:14 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "../Utils/Redirections/redirection.h"
#include "../Utils/Memory/memory.h"
#include "../Libft/libft.h"

void	handle_redirection_token(t_ast_node *current, t_token **token)
{
	if ((*token)->next)
		add_redirection(&current->redirections, *token);
	*token = (*token)->next;
}

void	handle_heredoc_token(t_ast_node *current, t_token **token,
			t_shell *shell)
{
	char	*filename;
	size_t	len;
	bool	quoted;

	if (!(*token)->next)
		return ;
	filename = (*token)->next->value;
	len = ft_strlen(filename);
	quoted = false;
	if (len > 1 && (filename[0] == '\'' || filename[0] == '"')
		&& filename[len - 1] == filename[0])
		quoted = true;
	shell->should_expand = false;
	add_redirection_with_quoted(&current->redirections, *token, quoted);
	*token = (*token)->next;
}

t_ast_node	*handle_pipe_token(t_ast_node *current)
{
	current->next_pipe = create_node();
	return (current->next_pipe);
}

void	add_arg(char ***args, char *value)
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
	i = 0;
	while ((*args)[i])
		i++;
	new_args = memory_malloc(sizeof(char *) * (i + 2));
	i = -1;
	while ((*args)[++i])
		new_args[i] = (*args)[i];
	new_args[i++] = ft_strdup(value);
	new_args[i] = NULL;
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
