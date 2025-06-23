/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:54 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:45:46 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Utils/Memory/memory.h"
#include "../../Utils/Status/status.h"
#include "unset.h"
#include <stdlib.h>

static int	match_key(char *entry, char *key)
{
	int	i;

	i = 0;
	while (entry[i] && key[i] && entry[i] == key[i])
		i++;
	return (key[i] == '\0' && (entry[i] == '=' || entry[i] == '\0'));
}

static int	env_count_except(char **env, char *key)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (env[i])
	{
		if (!match_key(env[i], key))
			count++;
		i++;
	}
	return (count);
}

static char	**remove_env_var(char **env, char *key)
{
	int		i;
	int		j;
	int		new_size;
	char	**new_env;

	i = 0;
	j = 0;
	new_size = env_count_except(env, key);
	new_env = memory_malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		if (!match_key(env[i], key))
			new_env[j++] = env[i];
		else
			memory_free(env[i]);
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	builtin_unset(char **args, t_shell *shell)
{
	int		i;
	char	**new_env;
	char	**old_env;

	i = 1;
	while (args[i])
	{
		old_env = shell->env;
		new_env = remove_env_var(shell->env, args[i]);
		if (new_env)
			shell->env = new_env;
		else
			return (set_exit_status(1), 1);
		memory_free(old_env);
		i++;
	}
	set_exit_status(0);
	return (0);
}
