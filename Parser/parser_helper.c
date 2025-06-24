/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 05:58:59 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 06:06:09 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../Utils/Memory/memory.h"
#include "../Libft/libft.h"
#include "../Utils/Redirections/redirection.h"

static void	add_arg(char ***args, char *value)
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

void	handle_word_token(t_ast_node *current, t_token *token, t_shell *shell)
{
	char	*processed;
	char	*expanded;

	if (token->type == T_SINGLE_QUOTE)
		shell->should_expand = false;
	else if (token->type == T_DOUBLE_QUOTE)
		shell->should_expand = true;
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

void	handle_redirection_token(t_ast_node *current,
	t_token **token_ptr, t_shell *shell)
{
	t_token	*token;
	char	*filename;
	size_t	len;
	bool	quoted;

	token = *token_ptr;
	if (token->next)
	{
		filename = token->next->value;
		len = ft_strlen(filename);
		quoted = false;
		if (len > 1 && (filename[0] == '\'' || filename[0] == '"')
			&& filename[len - 1] == filename[0])
			quoted = true;
		if (token->next->type == T_SINGLE_QUOTE
			|| token->next->type == T_DOUBLE_QUOTE)
			shell->should_expand = false;
		add_redirection_with_quoted(&current->redirections, token, quoted);
		*token_ptr = token->next;
	}
}

void	handle_pipe_token(t_ast_node **current)
{
	(*current)->next_pipe = create_node();
	*current = (*current)->next_pipe;
}
