/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:43:25 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:54:24 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Utils/Memory/memory.h"
#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	source_length;

	if (!s)
		return (NULL);
	source_length = ft_strlen(s);
	if (start >= source_length)
	{
		substring = (char *)memory_malloc(sizeof(char));
		if (!substring)
			return (NULL);
		*substring = '\0';
	}
	else
	{
		if ((source_length - start) < len)
			len = source_length - start;
		substring = (char *)memory_malloc((len + 1) * sizeof(char));
		if (!substring)
			return (NULL);
		ft_strlcpy(substring, (s + start), len + 1);
	}
	return (substring);
}
