/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:04 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/27 16:56:53 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief delete first var
/// @param preview_node 
/// @param node 
static void	ft_delete_firt_envnode(t_env *node)
{
	if (node->key_var)
	{
		free(node->key_var);
		node->key_var = NULL;
	}
	if (node->var)
	{
		free(node->var);
		node->var = NULL;
	}
	if (node)
		free(node);
}

/// @brief delete var
/// @param preview_node 
/// @param node 
static void	ft_delete_envnode(t_env *preview_node, t_env *node)
{
	preview_node->next = node->next;
	if (node->key_var)
	{
		free(node->key_var);
		node->key_var = NULL;
	}
	if (node->var)
	{
		free(node->var);
		node->var = NULL;
	}
	if (node)
		free(node);
}

void	node_trouver(t_command *cmd, t_env *tmp, t_env *preview)
{
	if (preview == NULL)
	{
		cmd->shell->env = tmp->next;
		ft_delete_firt_envnode(tmp);
	}
	else
		ft_delete_envnode(preview, tmp);
}

void	while_unset(t_command *cmd, t_env *tmp, t_env *preview)
{
	int		i;
	int		len;

	i = 1;
	while (cmd->av[i] || tmp)
	{
		len = (ft_strlen(cmd->av[i]) + 1);
		if (!tmp)
		{
			i++;
			tmp = cmd->shell->env;
			continue;
		}
		if (!ft_strncmp(cmd->av[i], tmp->key_var, len))
		{
			node_trouver(cmd, tmp, preview);
			tmp = cmd->shell->env;
			i++;
			continue;
		}
		preview = tmp;
		tmp = tmp->next;
	}
}

/// @brief check is a var and delete var
/// @param cmd 
void	buildin_unset(t_command *cmd)
{
	t_env	*tmp;
	t_env	*preview;

	if (!cmd->av[1])
		return ;
	preview = NULL;
	tmp = cmd->shell->env;
	while_unset(cmd, tmp, preview);
}
