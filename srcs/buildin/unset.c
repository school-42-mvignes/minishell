/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:04 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/21 16:10:28 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief delete var
/// @param preview_node 
/// @param node 
static void	ft_delete_envnode(t_env *preview_node, t_env *node)
{
	preview_node->next = node->next;
	free(node->key_var);
	node->key_var = NULL;
	free(node->var);
	node->var = NULL;
	free(node);
}

/// @brief check is a var and delete var
/// @param cmd 
void	buildin_unset(t_command *cmd)
{
	t_env	*tmp;
	t_env	*preview;
	int		len;

	len = (ft_strlen(cmd->av[1]) + 1);
	tmp = cmd->shell->env;
	while (tmp)
	{
		if (!ft_strncmp(cmd->av[1], tmp->key_var, len))
		{
			ft_delete_envnode(preview, tmp);
			break ;
		}
		preview = tmp;
		tmp = tmp->next;
	}
	free(tmp);
}
