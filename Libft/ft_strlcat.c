/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:58:38 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/23 15:58:41 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		dest_size;
	size_t		src_size;

	dest_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dstsize <= dest_size)
		return (src_size + dstsize);
	i = 0;
	while (src[i] && (dest_size + i) < (dstsize - 1))
	{
		dst[dest_size + i] = src[i];
		i++;
	}
	dst[dest_size + i] = '\0';
	return (dest_size + src_size);
}
