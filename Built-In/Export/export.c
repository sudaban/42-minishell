/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:45 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 14:18:27 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
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
			fprintf(stderr, "export: not a valid identifier\n");
		else if (!replace_env(args[i], &shell->env))
			shell->env = append_env(args[i], shell->env);
		i++;
	}
	return (0);
}
