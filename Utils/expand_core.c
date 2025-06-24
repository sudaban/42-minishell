/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 03:40:00 by itaskira          #+#    #+#             */
/*   Updated: 2025/06/24 03:22:11 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Status/status.h"
#include "../minishell.h"
#include "Memory/memory.h"
#include <stdio.h>
#include <stdlib.h>

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

int	expand_exit_status(char *result, int *j, int *i)
{
	char	*val;

	val = ft_itoa(get_last_exit_status());
	copy_var_value(result, j, val);
	memory_free(val);
	(*i)++;
	return (1);
}

int	handle_variable(const char *input, char *result, int *j,
		t_expand_data *data)
{
	char	var[256];
	char	*val;
	int		k;

	k = 0;
	while (input[data->i] && (ft_isalnum(input[data->i])
			|| input[data->i] == '_'))
		var[k++] = input[data->i++];
	var[k] = '\0';
	val = get_env_value(var, data->env);
	if (val)
	{
		copy_var_value(result, j, val);
		return (1);
	}
	return (0);
}

/* Bu fonksiyonlar expand_calc.c dosyasına taşınmıştır:
 * calc_exit_status_len
 * calc_var_len
 */
