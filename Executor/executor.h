/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:16:23 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/18 14:18:49 by itaskira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../Parser/parser.h"
# include "../minishell.h"

void	execute_ast(t_ast_node *ast, t_shell *shell);

#endif
