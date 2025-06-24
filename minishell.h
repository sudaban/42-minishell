/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:20 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 03:19:52 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h>

extern int		g_signal;

typedef struct s_shell
{
	char		**env;
	bool		debug;
	bool		should_expand;
	bool		in_heredoc;
}				t_shell;

typedef struct s_expand_data
{
	int			i;
	const char	*input;
	char		**env;
}				t_expand_data;

/* Environment functions */
char			*get_env_value(const char *key, char **env);

/* Expansion functions */
char			*expand_variables(const char *input, t_shell *shell);
void			copy_var_value(char *result, int *j, char *val);
int				expand_exit_status(char *result, int *j, int *i);
int				handle_variable(const char *input, char *result, int *j,
					t_expand_data *data);
int				calc_exit_status_len(void);
int				calc_var_len(const char *input, int *i, char **env);
int				calc_len(const char *input, char **env);
void			init_expand_data(t_expand_data *data, const char *input,
					t_shell *shell);

/* Execution functions */
char			*find_executable(char *cmd, char **env);
void			exec_external(char **args, char **env);

/* Syntax check */
bool			check_syntax(const char *input);
#endif
