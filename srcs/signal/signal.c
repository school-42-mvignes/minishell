/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:09:26 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/16 15:00:32 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int g_status = 0;

static void	controller(int sig)
{
	g_status = sig;
	write(1,"\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void init_signal(void)
{
	signal(SIGINT, controller);
	signal(SIGQUIT, SIG_IGN);
}