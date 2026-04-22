/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:41:56 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/21 16:00:00 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_node(t_node *node)
{
	t_redir	*tmp;

	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		free_tab(node->cmd->av);
		while (node->cmd->redir)
		{
			tmp = node->cmd->redir;
			free(tmp->file);
			node->cmd->redir = node->cmd->redir->next;
			free(tmp);
		}
		free(node->cmd);
	}
	else
	{
		free_node(node->left);
		free_node(node->right);
	}
	free(node);
}

void	free_malloc_fail(t_node *node, t_command *cmd)
{
	if (!cmd)
		free_node(node);
	else if (!cmd->av)
	{
		free(cmd);
		free_node(node);
	}
}