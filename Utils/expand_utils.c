/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 03:30:00 by itaskira          #+#    #+#             */
/*   Updated: 2025/06/24 03:22:19 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "../Utils/Status/status.h"
#include "../minishell.h"
#include "Memory/memory.h"
#include <stdio.h>
#include <stdlib.h>

void	init_expand_data(t_expand_data *data, const char *input, t_shell *shell)
{
	data->i = 0;
	data->input = input;
	data->env = shell->env;
}

static void	process_dollar_sign(char *result, t_expand_data *data, int *j)
{
	data->i++;
	if (data->input[data->i] == '?')
		expand_exit_status(result, j, &data->i);
	else
		handle_variable(data->input, result, j, data);
}

static char	*perform_expansion(const char *input, t_shell *shell)
{
	char			*result;
	t_expand_data	data;
	int				j;

	result = memory_malloc(calc_len(input, shell->env) + 1);
	if (!result)
		return (NULL);
	init_expand_data(&data, input, shell);
	j = 0;
	while (input[data.i])
	{
		if (input[data.i] == '$')
			process_dollar_sign(result, &data, &j);
		else
			result[j++] = input[data.i++];
	}
	result[j] = '\0';
	return (result);
}

char	*expand_variables(const char *input, t_shell *shell)
{
	if (!shell->should_expand)
		return (ft_strdup(input));
	return (perform_expansion(input, shell));
}
