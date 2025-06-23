/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:24 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:41:33 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Utils/Status/status.h"
#include "cd.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
