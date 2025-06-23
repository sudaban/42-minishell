/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:21:49 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:44:08 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"

int	*get_exit_status(void)
{
	static int	status;

	return (&status);
}

void	set_exit_status(int code)
{
	*get_exit_status() = code;
}

int	get_last_exit_status(void)
{
	return (*get_exit_status());
}
