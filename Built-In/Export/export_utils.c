/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:43 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:41:59 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Libft/libft.h"
#include "../../Utils/Memory/memory.h"
#include "export.h"
#include <stdlib.h>

int	is_valid_key(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	if (!(arg[i] == '_' || ft_isalpha(arg[i])))
		return (0);
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!(arg[i] == '_' || ft_isalnum(arg[i])))
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
	int		i;
	char	*value_control;

	i = 0;
	value_control = ft_strchr(new_entry, '=');
	if (!value_control)
	{
		while ((*env)[i])
		{
			if (key_match((*env)[i++], new_entry))
				return (1);
		}
		return (0);
	}
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
