/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:46:47 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 00:57:16 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

static t_memory	**get_mem_list(void)
{
	static t_memory	*mem_list = NULL;

	return (&mem_list);
}

void	*memory_malloc(size_t size)
{
	void		*ptr;
	t_memory	*new_node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_memory));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	new_node->ptr = ptr;
	new_node->next = *get_mem_list();
	*get_mem_list() = new_node;
	return (ptr);
}

void	memory_free(void *ptr)
{
	t_memory	**head;
	t_memory	*prev;
	t_memory	*cur;

	head = get_mem_list();
	prev = NULL;
	cur = *head;
	while (cur)
	{
		if (cur->ptr == ptr)
		{
			if (prev)
				prev->next = cur->next;
			else
				*head = cur->next;
			free(cur->ptr);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	memory_cleanup(int status)
{
	t_memory	*tmp;
	t_memory	**head;

	head = get_mem_list();
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->ptr);
		free(tmp);
	}
	rl_cleanup_after_signal();
	rl_clear_history();
	exit(status);
}
