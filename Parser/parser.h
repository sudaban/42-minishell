/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:35:38 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/16 17:15:25 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../Lexer/lexer.h"

typedef struct s_redirection
{
    t_token_type	type;
    char			*filename;
    struct s_redirection	*next;
}	t_redirection;

typedef struct s_ast_node
{
    char				**args;
    t_redirection		*redirections;
    struct s_ast_node	*next_pipe; // if pipe exists, next cmd
}	t_ast_node;

t_ast_node	*parse_tokens(t_token *tokens);
void		print_ast_debug(t_ast_node *ast);

#endif
