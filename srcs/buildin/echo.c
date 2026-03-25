/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:49 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 14:36:48 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buildin_echo(t_command *cmd) // 1
{
	int	i;

	i = 1;
	if (!ft_strncmp("-n", cmd->av[1], 3))
		i++;
	while (cmd->av[i])
	{
		if (i != 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmd->av[i++], 1);
	}
	if (ft_strncmp("-n", cmd->av[1], 3))
		ft_putchar_fd('\n', 1);
	return ;
}
