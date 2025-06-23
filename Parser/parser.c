/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:35:43 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:35:18 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../Libft/libft.h"
#include "../Utils/Memory/memory.h"
#include "../Utils/Redirections/redirection.h"

#include "parser.h"
#include "../Utils/Redirections/redirection.h"
#include "../Libft/libft.h"
#include <stdio.h>

static void	handle_word_token(t_ast_node *current,
	t_token *token, t_shell *shell)
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

static void	handle_heredoc_token(t_ast_node *current,
	t_token *token, t_shell *shell)
{
	char	*filename;
	size_t	len;
	bool	quoted;

	if (!token->next)
		return ;
	filename = token->next->value;
	len = ft_strlen(filename);
	quoted = false;
	if (len > 1 && (filename[0] == '\'' || filename[0] == '"')
		&& filename[len - 1] == filename[0])
		quoted = true;
	if (token->next->type == T_SINGLE_QUOTE || token->next->type == 2)
		shell->should_expand = false;
	add_redir_quoted(&current->redirections, token, quoted);
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
			init_node(&head, &current);
		if (is_word_token(token))
			handle_word_token(current, token, shell);
		else if (is_redirection_token(token))
			handle_redirect_token(&token, current);
		else if (token->type == T_HEREDOC)
			handle_heredoc_token(current, token, shell);
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
