/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:53 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/21 13:35:46 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
static void	not_num_exit(t_command *cmd)
{
	write(2, "minishell: exit: ", 17);
	write(2, cmd->av[1], ft_strlen(cmd->av[1]));
	write(2, ": numeric argument required\n", 28);
	free_exit(cmd);
	exit(2);
}

static	int check_overflow(long long res, int last_digit, int si, int *error)
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
static	long long	ft_atoll(char *str, int *error)
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

int	buildin_exit(t_command *cmd)
{
	long long	num_exit;
	int			error;
	int status;

	status = 0;
	error = 0;
	write(2, "exit\n", 5);
	if (cmd->av[1] && cmd->av[2])
	{
		write(2, "minishell: exit: ", 17);
		write(2, "too many arguments\n", 19);
		cmd->shell->exit_status = 1;
		return (1);
	}
	if (cmd->av[1] && !is_num(cmd->av[1]))
		not_num_exit(cmd);
	if (cmd->av[1])
	{
		num_exit = ft_atoll(cmd->av[1], &error);
		if (error)
			not_num_exit(cmd);
		cmd->shell->exit_status = ((num_exit % 256) + 256) % 256;
		status = cmd->shell->exit_status;
		free_exit(cmd);
		exit(status);
	}
	status = cmd->shell->exit_status;
	free_exit(cmd);
	exit(status);
}
