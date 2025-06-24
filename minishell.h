/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:20 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 06:20:25 by sdaban           ###   ########.fr       */
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

typedef struct s_expand_context
{
	const char	*input;
	char		*result;
	int			i;
	int			j;
	t_shell		*shell;
}	t_expand_context;

char		*get_env_value(const char *key, char **env);
char		*expand_variables(const char *input, t_shell *shell);
char		*find_executable(char *cmd, char **env);
void		exec_external(char **args, char **env);
bool		check_syntax(const char *input);
void		copy_var_value(char *result, int *j, char *val);
int			calc_len(const char *input, char **env);
char		*get_cmd_path(char *cmd, char **env);
char		*get_cmd_path_and_check(char *cmd, char **env);
void		exec_child_process(char *cmd, char **args, char **env);
void		exec_parent_process(int pid, int *status);
void		handle_variable_expansion(t_expand_context *ctx);
#endif
