/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:20 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:44:43 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h>

extern int	g_signal;

typedef struct s_shell
{
	char	**env;
	bool	debug;
	bool	should_expand;
	bool	in_heredoc;
}			t_shell;

char		*get_env_value(const char *key, char **env);
char		*expand_variables(const char *input, t_shell *shell);
char		*find_executable(char *cmd, char **env);
void		exec_external(char **args, char **env);
bool		check_syntax(const char *input);
#endif
