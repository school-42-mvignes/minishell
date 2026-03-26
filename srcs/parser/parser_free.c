/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:41:56 by mmusquer          #+#    #+#             */
/*   Updated: 2026/03/26 18:26:24 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_node(t_node *node)
{
	int		i;
	t_redir	*tmp;

	i = 0;
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		free(node->cmd->av);
		while (node->cmd->redir)
		{
			tmp = node->cmd->redir;
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
