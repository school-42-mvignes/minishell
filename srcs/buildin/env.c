/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:22:03 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/16 19:19:09 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error_env(t_command *cmd)
{
	ft_putstr_fd("env: '", 1);
	ft_putstr_fd(cmd->av[1], 1);
	ft_putendl_fd("': No such file or directory", 1);
}

void	buildin_env(t_command *cmd)
{
	if (!cmd->av[1])
		printf_env(cmd->shell->env);
	else
		print_error_env(cmd);
}
