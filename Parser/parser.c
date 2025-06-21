/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:35:43 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/21 17:27:37 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "../Utils/Redirections/redirection.h"
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
	for (i = 0; (*args)[i]; i++);
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

	new = memory_malloc(sizeof(t_redirection));
	new->type = token->type;
	new->filename = ft_strdup(token->next->value); // file name after redirection
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		t_redirection *tmp = *list;
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

t_ast_node	*parse_tokens(t_token *token, t_shell *shell)
{
	t_ast_node	*head = NULL;
	t_ast_node	*current = NULL;
	char		*processed = NULL;

	while (token && token->type != T_EOF)
	{
		if (!current)
		{
			current = create_node();
			if (!head)
				head = current;
		}
		if (token->type == T_WORD || token->type == T_ENV_VAR ||
			token->type == T_DOUBLE_QUOTE || token->type == T_SINGLE_QUOTE)
		{
			if (token->type == T_SINGLE_QUOTE)
				shell->should_expand = false;
			else if (token->type == T_DOUBLE_QUOTE)
				shell->should_expand = true;
			
			processed = clean_quotes(token->value, shell);
			if (shell->should_expand)
			{
				char *expanded = expand_variables(processed, shell);
				add_arg(&current->args, expanded);
				memory_free(expanded);
			}
			else
			{
				add_arg(&current->args, processed);
			}
			memory_free(processed);
		}
		 else if (token->type == T_REDIRECT_IN || token->type == T_REDIRECT_OUT ||
                 token->type == T_APPEND_OUT)
        {
            if (token->next)
                add_redirection(&current->redirections, token);
            token = token->next; // skip filename
        }
		else if (token->type == T_HEREDOC)
        {
            if (token->next)
            {
                char *filename = token->next->value;
                size_t len = ft_strlen(filename);
                bool quoted = false;

                if (len > 1 && (filename[0] == '\'' || filename[0] == '"') && filename[len - 1] == filename[0])
                    quoted = true;
				if (token->next->type == T_SINGLE_QUOTE || token->next->type == T_DOUBLE_QUOTE)
					shell->should_expand = false;
				printf("Token: %s, should_expand=%i\n", token->next->value, shell->should_expand);
                add_redirection_with_quoted(&current->redirections, token, quoted);
                token = token->next; // skip filename
            }
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
	int	i;
	t_redirection *redir;

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
