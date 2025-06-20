/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:54 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/20 16:09:02 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"
#include <stdlib.h>
#include "../../Utils/Memory/memory.h"
#include "../../Utils/Status/status.h"

static int	match_key(char *entry, char *key)
{
	int	i;

	i = 0;
	while (key[i] && entry[i] && key[i] == entry[i])
		i++;
	if (key[i] == '\0' && entry[i] == '=')
		return (1);
	return (0);
}

static char	**remove_env_var(char **env, char *key)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;

	count = 0;
	while (env[count])
		count++;
	new_env = memory_malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (match_key(env[i], key))
			memory_free(env[i]); // check env free
		else
			new_env[j++] = env[i];
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		shell->env = remove_env_var(shell->env, args[i]);
		i++;
	}
	set_exit_status(0);
	return (0);
}
