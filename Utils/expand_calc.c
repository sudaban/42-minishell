/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 03:45:00 by itaskira          #+#    #+#             */
/*   Updated: 2025/06/24 03:19:54 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Status/status.h"
#include "../minishell.h"
#include "Memory/memory.h"
#include <stdio.h>
#include <stdlib.h>

int	calc_exit_status_len(void)
{
	char	*val;
	int		len;

	val = ft_itoa(get_last_exit_status());
	len = ft_strlen(val);
	memory_free(val);
	return (len);
}

int	calc_var_len(const char *input, int *i, char **env)
{
	char	var[256];
	char	*val;
	int		k;
	int		len;

	k = 0;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		var[k++] = input[(*i)++];
	var[k] = '\0';
	val = get_env_value(var, env);
	if (val)
		len = ft_strlen(val);
	else
		len = 0;
	return (len);
}

int	calc_len(const char *input, char **env)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '?')
			{
				len += calc_exit_status_len();
				i++;
			}
			else
				len += calc_var_len(input, &i, env);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
