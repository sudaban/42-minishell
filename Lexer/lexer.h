/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:52:55 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/20 15:07:17 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"

typedef enum e_token_type
{
	T_WORD,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_PIPE,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND_OUT,
	T_HEREDOC,
	T_ENV_VAR,
	T_EXIT_STATUS,
	T_NEWLINE,
	T_EOF,
	T_OR,
	T_AND,
	T_AMPERSAND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token		*lexer(const char *input);
void		print_token_debug(t_token *tokens);
char		*clean_quotes(const char *input, t_shell *shell);
#endif