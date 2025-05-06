/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:39:41 by sdaban            #+#    #+#             */
/*   Updated: 2025/05/06 16:15:00 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_double_ptr(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		i++;
	while (--i >= 0)
	{
		if (str[i])
			free(str[i]);
	}
	free(str);
}
