/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:16:23 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/17 13:52:12 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../Parser/parser.h"
# include "../minishell.h"

void	execute_ast(t_ast_node *ast, t_shell *shell);

#endif
