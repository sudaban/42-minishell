/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:20 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:39:02 by sdaban           ###   ########.fr       */
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
void		copy_var_value(char *result, int *j, char *val);
int			calc_len(const char *input, char **env);
char		*get_cmd_path(char *cmd, char **env);
#endif
