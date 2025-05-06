/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:46 by sdaban            #+#    #+#             */
/*   Updated: 2025/05/06 16:23:47 by sdaban           ###   ########.fr       */
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
