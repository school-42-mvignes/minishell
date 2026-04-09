/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:53 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/08 16:14:52 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_exit_cut(t_command *cmd)
{
	write(2, "minishell: exit: ", 6);
	write(2, cmd->av[1], ft_strlen(cmd->av[1]));
	write(2, ": numeric argument required\n", 28);
}

static int	exit_cut(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->av[2])
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 25);
		i = 0;
	}
	i = 1;
	return (i);
}

int	buildin_exit(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd->av[1])
	{
		write(2, "exit\n", 5);
		return (1);
	}
	if (exit_cut(cmd) == 0)
		return (0);
	if (cmd->av[1][i] == '+' || cmd->av[1][i] == '-')
		i++;
	while (cmd->av[1][i])
	{
		if (cmd->av[1][i] < '0' || cmd->av[1][i] > '9')
		{
			write_exit_cut(cmd);
			cmd->shell->exit_status = 2;
			return (1);
		}
		i++;
	}
	cmd->shell->exit_status = (ft_atoi(cmd->av[1]) % 256);
	write(2, "exit\n", 5);
	return (1);
}
