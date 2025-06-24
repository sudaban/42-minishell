/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:35:38 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 06:05:15 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../Lexer/lexer.h"
# include <stdbool.h>

typedef struct s_redirection
{
	t_token_type			type;
	char					*filename;
	bool					quoted;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_ast_node
{
	char					**args;
	t_redirection			*redirections;
	struct s_ast_node		*next_pipe;
}							t_ast_node;

t_ast_node	*parse_tokens(t_token *tokens, t_shell *shell);
void		print_ast_debug(t_ast_node *ast);
void		handle_word_token(t_ast_node *current,
				t_token *token, t_shell *shell);
void		handle_redirection_token(t_ast_node *current,
				t_token **token_ptr, t_shell *shell);
void		handle_pipe_token(t_ast_node **current);
t_ast_node	*create_node(void);
#endif
