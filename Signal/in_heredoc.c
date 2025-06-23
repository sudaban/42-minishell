/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaskira <itaskira@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:33:07 by sdaban            #+#    #+#             */
/*   Updated: 2025/06/24 01:43:38 by itaskira         ###   ########.fr       */
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
