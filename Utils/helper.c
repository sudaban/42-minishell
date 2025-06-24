/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 05:30:21 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:33:44 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Status/status.h"
#include "../minishell.h"
#include "Memory/memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../Signal/signal.h"

void	copy_var_value(char *result, int *j, char *val)
{
	int	m;

	m = 0;
	while (val[m])
	{
		if (val[m] != '\'' && val[m] != '\"')
			result[(*j)++] = val[m];
		m++;
	}
}

static int	process_dollar_sign(const char **input, char **env)
{
	int		len;
	int		k;
	char	var[256];
	char	*val;

	len = 0;
	(*input)++;
	if (**input == '?')
	{
		val = ft_itoa(get_last_exit_status());
		len += ft_strlen(val);
		memory_free(val);
		(*input)++;
	}
	else
	{
		k = 0;
		while (**input && (ft_isalnum(**input) || **input == '_'))
			var[k++] = *((*input)++);
		var[k] = '\0';
		val = get_env_value(var, env);
		if (val)
			len += ft_strlen(val);
	}
	return (len);
}

int	calc_len(const char *input, char **env)
{
	int	len;

	len = 0;
	while (*input)
	{
		if (*input == '$')
		{
			len += process_dollar_sign(&input, env);
		}
		else
		{
			len++;
			input++;
		}
	}
	return (len);
}

char	*get_cmd_path(char *cmd, char **env)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (find_executable(cmd, env));
}
