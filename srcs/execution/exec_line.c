/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:27:15 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/14 13:02:49 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief dispatches in the correct execution following the node
/// @param node 
void	exec_node(t_node *node)
{
	if (node->type == NODE_CMD)
		exec_node_cmd(node);
	else if (node->type == NODE_PIPE)
		exec_pipe(node);
	else if (node->type == NODE_AND)
		exec_and(node);
	else if (node->type == NODE_OR)
		exec_or(node);
}
