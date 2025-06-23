/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:35:38 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:36:51 by sdaban           ###   ########.fr       */
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

t_ast_node	*parse_tokens(t_token *token, t_shell *shell);

bool		is_word_token(t_token *token);
bool		is_redirection_token(t_token *token);
void		init_node(t_ast_node **head, t_ast_node **current);
void		handle_redirect_token(t_token **token, t_ast_node *current);
void		handle_pipe_token(t_ast_node **current);
void		print_ast_debug(t_ast_node *ast);
void		add_arg(char ***args, char *value);
t_ast_node	*create_node(void);
void		add_redirection(t_redirection **list, t_token *token);

#endif
