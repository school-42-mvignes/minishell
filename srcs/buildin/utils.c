/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:46:03 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/16 14:48:38 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief check if he’s a buildin
/// @param node 
/// @return true or false
bool	is_one_buildin(t_node *node)
{
	if (!ft_strncmp(ECHO, node->cmd->av[0], 5)
		|| !ft_strncmp(CD, node->cmd->av[0], 3)
		|| !ft_strncmp(PWD, node->cmd->av[0], 4)
		|| !ft_strncmp(ENV, node->cmd->av[0], 4)
		|| !ft_strncmp(EXPORT, node->cmd->av[0], 7)
		|| !ft_strncmp(UNSET, node->cmd->av[0], 6)
		|| !ft_strncmp(EXIT, node->cmd->av[0], 5))
		return (true);
	return (false);
}

/// @brief Check if he is in a trap and whether to launch a fork or not on the buildin cd, export, unset
/// @param node 
/// @return true = exec_without_fork, false exec_with_fork
bool	exec_without_fork(t_node *node)
{
	if (!node->in_pipe &&
	(!ft_strncmp(CD, node->cmd->av[0], 3)
	|| !ft_strncmp(EXPORT, node->cmd->av[0], 7)
	|| !ft_strncmp(UNSET, node->cmd->av[0], 6)))
		return (true);
	return (false);
}

/// @brief executes the right build without being in a fork
/// @param node 
void	exec_buildin_without_fork(t_node *node)
{
	if (!ft_strncmp(CD, node->cmd->av[0], 3))
		buildin_cd(node->cmd);
	else if (!ft_strncmp(PWD, node->cmd->av[0], 4))
		buildin_pwd(node->cmd);
	else if (!ft_strncmp(ENV, node->cmd->av[0], 4))
		buildin_env(node->cmd);
	else if (!ft_strncmp(EXPORT, node->cmd->av[0], 7))
		buildin_export(node->cmd);
	else if (!ft_strncmp(UNSET, node->cmd->av[0], 6))
		buildin_unset(node->cmd);
}
