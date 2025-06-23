/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:16:23 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:41:09 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../Parser/parser.h"
# include "../minishell.h"

typedef struct s_pipe_data
{
	int			input_fd;
	int			pipefd[2];
	int			has_next;
	t_ast_node	*current;
	t_shell		*shell;
}				t_pipe_data;

void			execute_ast(t_ast_node *ast, t_shell *shell);
void			execute_pipeline(t_ast_node *ast, t_shell *shell);
void			execute_command(char **args, t_shell *shell);
void			setup_input_output(t_pipe_data *data);
void			execute_child_process(t_pipe_data *data);
void			prepare_pipe_data(t_pipe_data *data, t_ast_node *current,
					int *input_fd, t_shell *shell);
void			cleanup_pipe_fds(t_pipe_data *data, int *input_fd);

#endif
