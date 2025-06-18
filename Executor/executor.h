/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:16:23 by sdaban            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/18 14:18:49 by itaskira         ###   ########.fr       */
=======
/*   Updated: 2025/06/18 12:50:17 by sdaban           ###   ########.fr       */
>>>>>>> 3e499a59db7651945e676177aab591ce37ace637
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../Parser/parser.h"
# include "../minishell.h"

void	execute_ast(t_ast_node *ast, t_shell *shell);
void	execute_pipeline(t_ast_node *ast, t_shell *shell);
void	execute_command(char **args, t_shell *shell);
#endif
