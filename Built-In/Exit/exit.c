/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:39 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 00:59:06 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include "../../Libft/libft.h"
#include "../../Utils/Status/status.h"
#include "../../Utils/Memory/memory.h"

static int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	long	exit_code;
	int		status;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
	{
		memory_cleanup(get_last_exit_status() % 256);
	}
	status = ft_atol(args[1], &exit_code);
	if (!is_numeric(args[1]) || status == -1)
	{
		ft_putstr_fd("Born2Exec: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		memory_cleanup(255);
	}
	if (args[2])
	{
		ft_putendl_fd("Born2Exec: exit: too many arguments", STDERR_FILENO);
		set_exit_status(1);
		return (1);
	}
	memory_cleanup((unsigned char)(exit_code % 256));
	return (1337);
}
