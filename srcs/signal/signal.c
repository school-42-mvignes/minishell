/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:09:26 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/28 11:32:59 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		g_status = 0;

void	controller(int sig)
{
	g_status = sig;
	write(2, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGINT, controller);
}

void	init_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, controller);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_controller(int sig)
{
	(void)sig;
	g_status = SIGINT;
	close (0);
}
