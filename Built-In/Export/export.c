/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:45 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 06:28:16 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../Utils/Status/status.h"
#include "../../minishell.h"
#include "export.h"
#include <stdio.h>
#include <unistd.h>

static int	builtin_export_no_args(t_shell *shell)
{
	int		i;
	char	*eq;

	i = 0;
	while (shell->env[i])
	{
		eq = ft_strchr(shell->env[i], '=');
		if (eq)
		{
			*eq = '\0';
			printf("declare -x %s=\"%s\"\n", shell->env[i], eq + 1);
			*eq = '=';
		}
		else
			printf("declare -x %s\n", shell->env[i]);
		i++;
	}
	set_exit_status(0);
	return (0);
}

int	builtin_export(char **args, t_shell *shell)
{
	int	i;

	if (!args[1])
		return (builtin_export_no_args(shell));
	i = 1;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
			ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
		else if (!replace_env(args[i], &shell->env))
			shell->env = append_env(args[i], shell->env);
		i++;
	}
	set_exit_status(0);
	return (0);
}
