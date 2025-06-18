/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:23:24 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 14:17:59 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (1);
		}
		path = home;
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
