/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:41:56 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/27 18:28:32 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_redir(t_node *node)
{
	t_redir	*tmp;

	tmp = node->cmd->redir;
	free(tmp->file);
	if (tmp->heredoc_fd > 0)
		close(tmp->heredoc_fd);
	node->cmd->redir = node->cmd->redir->next;
	free(tmp);
}

void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		if (node->cmd)
		{
			free_tab(node->cmd->av);
			while (node->cmd->redir)
			{
				free_node_cut(node);
			}
			free(node->cmd);
		}
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
