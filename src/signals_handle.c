/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontagn <gfontagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:28:47 by gfontagn          #+#    #+#             */
/*   Updated: 2025/06/02 18:35:06 by gfontagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_interactive(int sig)
{
	g_signal = sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_heredoc(int sig)
{
	g_signal = sig;
}

int	check_heredoc_signal(void)
{
	if (g_signal == SIGINT)
	{
		rl_done = 1;
		return (0);
	}
	return (0);
}
