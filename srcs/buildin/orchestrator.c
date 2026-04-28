/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:25:03 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/27 17:56:29 by mvignes          ###   ########.fr       */
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
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/// @brief perform the correct buildin
/// @param node 
/// @return 
int	exec_the_buildin(t_node *node, t_shell *shell)
{
	int	status;

	status = 0;
	if (node->cmd->av[0] == NULL)
		return (0);
	else if (!ft_strncmp(ECHOS, node->cmd->av[0], 5))
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
		if (buildin_exit(node->cmd))
			return (shell->exit_status);
	shell->exit_status = 0;
	status = shell->exit_status;
	exit_free_all(shell->free_the_token, shell->free_the_node, shell, NULL);
	exit(status);
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
	else if (!ft_strncmp(EXIT, node->cmd->av[0], 5))
		buildin_exit(node->cmd);
}
