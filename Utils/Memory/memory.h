/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:46:49 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/11 14:21:27 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
typedef struct s_memory {
    void			*ptr;
    struct s_memory	*next;
}	t_memory;


void	*memory_malloc(size_t size);
void	memory_free(void *ptr);
void	memory_cleanup();

#endif