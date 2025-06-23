/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:22:30 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:54:28 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Utils/Memory/memory.h"
#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*str2;
	size_t	len;

	len = ft_strlen(s1);
	str2 = (char *)memory_malloc(len + 1);
	if ((str2) == NULL)
		return (NULL);
	ft_memcpy(str2, s1, len + 1);
	return (str2);
}
