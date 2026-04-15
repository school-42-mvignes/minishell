/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:25:03 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/15 16:43:48 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief searches for the called variable
/// @param env 
/// @param key 
/// @return return the node search or returns NULL
t_env	*search_key_var(t_env *env, char *key)
{
	t_env	*tmp;
	int		len;
	
	len = (ft_strlen(key) + 1);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key_var, len))
			return(tmp);
		tmp = tmp->next;
	}
	return (NULL);
}


/*
==============================================================================
FAUT REVOIR CA PARCE QUE CA VA PAS, ON RETURN L EXIT STATUS ET 1 EN CAS D'EXIT
==============================================================================
*/
/// @brief perform the correct buildin
/// @param node 
/// @return 
int	exec_the_buildin(t_node *node)
{
	if (node->cmd->av[0] == NULL)
		return (0);
	else if (!ft_strncmp(ECHO, node->cmd->av[0], 5))
		buildin_echo(node->cmd);
	else if (!ft_strncmp(CD, node->cmd->av[0], 3))
		buildin_cd(node->cmd);
	else if (!ft_strncmp(PWD, node->cmd->av[0], 4))
		buildin_pwd(node->cmd);
	else if (!ft_strncmp(ENV, node->cmd->av[0], 4))
		buildin_env(node->cmd);
	else if (!ft_strncmp(EXPORT, node->cmd->av[0], 7))
		buildin_export(node->cmd);
	else if (!ft_strncmp(UNSET, node->cmd->av[0], 6))
		buildin_unset(node->cmd);
	else if (!ft_strncmp(EXIT, node->cmd->av[0], 5))
	{
		if (buildin_exit(node->cmd))
			return (1);
	}
	exit(node->cmd->shell->exit_status);
	return (0);
}
