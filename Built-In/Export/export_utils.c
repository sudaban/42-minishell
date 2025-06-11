/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:43 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/11 17:10:13 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "export.h"
#include "../../Libft/libft.h"
#include "../../Utils/Memory/memory.h"
int	is_valid_key(char *arg)
{
	int	i;

	if (!arg || !(arg[0] == '_' || (arg[0] >= 'A' && arg[0] <= 'Z')
			|| (arg[0] >= 'a' && arg[0] <= 'z')))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(arg[i] == '_' || (arg[i] >= 'A' && arg[i] <= 'Z')
				|| (arg[i] >= 'a' && arg[i] <= 'z')
				|| (arg[i] >= '0' && arg[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

static int	key_match(char *env_entry, char *new_entry)
{
	int	i;

	i = 0;
	while (new_entry[i] && new_entry[i] != '=')
	{
		if (env_entry[i] != new_entry[i])
			return (0);
		i++;
	}
	return (env_entry[i] == '=');
}

int	replace_env(char *new_entry, char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (key_match((*env)[i], new_entry))
		{
			memory_free((*env)[i]);
			(*env)[i] = ft_strdup(new_entry);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**append_env(char *new_entry, char **env)
{
	int		count;
	char	**new_env;

	count = 0;
	while (env[count])
		count++;
	new_env = memory_malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	count = 0;
	while (env[count])
	{
		new_env[count] = env[count];
		count++;
	}
	new_env[count++] = ft_strdup(new_entry);
	new_env[count] = NULL;
	return (new_env);
}
