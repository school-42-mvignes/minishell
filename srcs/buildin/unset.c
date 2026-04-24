/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:04 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/24 15:14:58 by mvignes          ###   ########.fr       */
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

/// @brief check is a var and delete var
/// @param cmd 
void	buildin_unset(t_command *cmd)
{
	t_env	*tmp;
	t_env	*preview;
	int		len;

	preview = NULL;
	len = (ft_strlen(cmd->av[1]) + 1);
	tmp = cmd->shell->env;
	while (tmp)
	{
		if (!ft_strncmp(cmd->av[1], tmp->key_var, len))
		{
			if (preview == NULL)
			{
				cmd->shell->env = tmp->next;
				ft_delete_firt_envnode(tmp);
			}
			else
				ft_delete_envnode(preview, tmp);
			break ;
		}
		preview = tmp;
		tmp = tmp->next;
	}
}
