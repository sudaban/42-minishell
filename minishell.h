/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:20 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/20 15:01:36 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_shell
{
	char	**env;
	bool	debug;
	bool	should_expand;
}	t_shell;

char	*get_env_value(const char *key, char **env);
char	*expand_variables(const char *input, t_shell *shell);
char	*find_executable(char *cmd, char **env);
void	exec_external(char **args, char **env);
bool	check_syntax(const char *input);
#endif
