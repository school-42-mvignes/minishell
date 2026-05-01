/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:53 by mvignes           #+#    #+#             */
/*   Updated: 2026/05/01 10:36:04 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	not_num_exit(t_command *cmd)
{
	write(2, "minishell: exit: ", 17);
	write(2, cmd->av[1], ft_strlen(cmd->av[1]));
	write(2, ": numeric argument required\n", 28);
	free_exit(cmd);
	exit(2);
}

static int	check_overflow(long long res, int last_digit, int si, int *error)
{
	if (si == 1)
	{
		if (res > LLONG_MAX / 10 || (res == LLONG_MAX / 10 && last_digit > 7))
		{
			*error = 1;
			return (1);
		}
	}
	else
	{
		if (res > LLONG_MAX / 10 || (res == LLONG_MAX / 10 && last_digit > 8))
		{
			*error = 1;
			return (1);
		}
	}
	return (0);
}

static long long	ft_atoll(char *str, int *error)
{
	int			i;
	int			si;
	long long	res;

	i = 0;
	si = 1;
	res = 0;
	if (str[i] == ' ' || (str[i] > 9 && str[i] < 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			si = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_overflow(res, str[i] - '0', si, error))
			return (0);
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * si);
}

static void	do_atoll(t_command *cmd, int *error, int *status)
{
	long long	num_exit;

	num_exit = ft_atoll(cmd->av[1], error);
	if (*error)
		not_num_exit(cmd);
	cmd->shell->exit_status = ((num_exit % 256) + 256) % 256;
	*status = cmd->shell->exit_status;
	free_exit(cmd);
	exit(*status);
}

int	builtin_exit(t_command *cmd)
{
	int	error;
	int	status;

	status = 0;
	error = 0;
	if (cmd->shell->forking == 0)
		write(2, "exit\n", 5);
	if (cmd->av[1] && !is_num(cmd->av[1]))
		not_num_exit(cmd);
	else if (cmd->av[1] && cmd->av[2])
	{
		write(2, "minishell: exit: ", 17);
		write(2, "too many arguments\n", 19);
		cmd->shell->exit_status = 1;
		return (1);
	}
	else if (cmd->av[1])
		do_atoll(cmd, &error, &status);
	status = cmd->shell->exit_status;
	free_exit(cmd);
	exit(status);
}
