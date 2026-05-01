/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:04 by mvignes           #+#    #+#             */
/*   Updated: 2026/05/01 10:28:52 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief check if he’s a buildin
/// @param node 
/// @return true or false
bool	is_one_buildin(t_node *node)
{
	if (!ft_strncmp(ECHOS, node->cmd->av[0], 5)
		|| !ft_strncmp(CD, node->cmd->av[0], 3)
		|| !ft_strncmp(PWD, node->cmd->av[0], 4)
		|| !ft_strncmp(ENV, node->cmd->av[0], 4)
		|| !ft_strncmp(EXPORT, node->cmd->av[0], 7)
		|| !ft_strncmp(UNSET, node->cmd->av[0], 6)
		|| !ft_strncmp(EXIT, node->cmd->av[0], 5))
		return (true);
	return (false);
}

/// @brief Check if he is in a trap and whether to launch a fork
/// or not on the buildin cd, export, unset
/// @param node 
/// @return true = exec_without_fork, false exec_with_fork
bool	exec_without_fork(t_node *node)
{
	if (node->in_pipe)
		return (false);
	if (!ft_strncmp(CD, node->cmd->av[0], 3)
		|| !ft_strncmp(EXPORT, node->cmd->av[0], 7)
		|| !ft_strncmp(UNSET, node->cmd->av[0], 6)
		|| !ft_strncmp(EXIT, node->cmd->av[0], 5))
		return (true);
	return (false);
}

void	free_exit(t_command *cmd)
{
	free_token_lst(cmd->shell->free_the_token);
	free_node(cmd->shell->free_the_node);
}

/// @brief check if its a number
/// @param str
/// @return true or false
int	is_num(char *str)
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
