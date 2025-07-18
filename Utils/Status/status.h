/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:21:26 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 02:10:47 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

# include <stdbool.h>

int		*get_exit_status(void);
void	set_exit_status(int stat);
int		get_last_exit_status(void);
void	handle_exit_status(int status, const char *message, bool should_exit);
#endif
