/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:22:03 by mvignes           #+#    #+#             */
/*   Updated: 2026/05/01 10:36:03 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief write error env
/// @param cmd 
static void	print_error_env(t_command *cmd)
{
	ft_putstr_fd("env: '", 2);
	ft_putstr_fd(cmd->av[1], 2);
	ft_putendl_fd("': No such file or directory", 2);
}

/// @brief check print or error env
/// @param cmd 
void	builtin_env(t_command *cmd)
{
	if (!cmd->av[1])
		print_env(cmd->shell->env);
	else
		print_error_env(cmd);
}
