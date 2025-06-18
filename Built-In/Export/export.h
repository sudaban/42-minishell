/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:46 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 14:18:28 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "../../minishell.h"

int		builtin_export(char **args, t_shell *shell);
int		is_valid_key(char *arg);
int		replace_env(char *new_entry, char ***env);
char	**append_env(char *new_entry, char **env);
char	*str_dup(const char *src);

#endif
