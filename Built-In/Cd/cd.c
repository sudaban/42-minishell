/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:24 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/21 16:57:56 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "../../Utils/Status/status.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	builtin_cd(char **args)
{
	char	*path;
	char	*home;

	if (!args[1] || (args[1][0] == '~' && args[1][0]))
	{
		home = getenv("HOME");
		if (!home)
		{
			write(2, "cd: HOME not set\n", 18);
			set_exit_status(1);
			return (1);
		}
		path = home;
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		set_exit_status(1);
		return (1);
	}
	set_exit_status(0);
	return (0);
}
