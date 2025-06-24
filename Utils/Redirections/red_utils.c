/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 05:11:27 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 05:16:33 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "../../Utils/Memory/memory.h"
#include <stdlib.h>
#include <readline/readline.h>
#include "../../Libft/libft.h"
#include "../../Utils/Status/status.h"

char	*get_filename_with_quotes(t_token *token, bool quoted)
{
	if (quoted)
		return (ft_substr(token->next->value, 1,
				ft_strlen(token->next->value) - 2));
	return (ft_strdup(token->next->value));
}

int	check_heredoc_interrupt(char *line, int *pipefd)
{
	if (!line || get_last_exit_status() == 130)
	{
		if (line)
			free(line);
		close(pipefd[0]);
		close(pipefd[1]);
		return (1);
	}
	return (0);
}

void	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

int	read_heredoc_lines(int *pipefd, const char *delimiter,
	bool expand, t_shell *shell)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		g_signal = 1;
		line = readline("> ");
		if (check_heredoc_interrupt(line, pipefd))
			return (-1);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
			expanded = expand_variables(line, shell);
		else
			expanded = ft_strdup(line);
		write_heredoc_line(pipefd[1], expanded);
		free(line);
		memory_free(expanded);
	}
	return (0);
}
