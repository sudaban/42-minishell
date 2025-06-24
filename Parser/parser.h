/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:35:38 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:38:40 by itaskira         ###   ########.fr       */
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

t_ast_node					*parse_tokens(t_token *tokens, t_shell *shell);
void						print_ast_debug(t_ast_node *ast);

#endif
