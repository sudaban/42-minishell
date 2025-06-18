/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:20 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 14:19:24 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_shell
{
	char	**env;
	bool	debug;
}			t_shell;

char		*get_env_value(const char *key, char **env);
char		*expand_variables(const char *input, char **env);
char		*find_executable(char *cmd, char **env);
void		exec_external(char **args, char **env);

#endif
