/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:41:56 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/22 15:27:36 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void	free_node(t_node *node)
{
	t_redir	*tmp;
	t_redir	*suivant;

	suivant = NULL;
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		if (node->cmd->av)
			free_tab(node->cmd->av);
		tmp = node->cmd->redir;
		while (tmp)
		{
			if (tmp->next)
				tmp->next = suivant;
			// tmp = node->cmd->redir;
			if (tmp)
			{
				free(tmp->file);
				free(tmp);
			}
			// node->cmd->redir = node->cmd->redir->next;
			if (suivant)
				tmp = suivant;
		}
		free(node->cmd);
	}
	else
	{
		free_node(node->left);
		free_node(node->right);
	}
	free(node);
} */

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