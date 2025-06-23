/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdaban <sdaban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:33:07 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/23 12:33:22 by sdaban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*heredoc_state_ptr(void)
{
	static int	in_heredoc;

	return (&in_heredoc);
}

void	set_heredoc_state(int state)
{
	*heredoc_state_ptr() = state;
}

int	heredoc_state(void)
{
	return (*heredoc_state_ptr());
}
