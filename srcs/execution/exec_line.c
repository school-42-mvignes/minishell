/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:27:15 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/27 17:28:38 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void	exec_in_the_subshell(t_node *node)
{
	
} */

/// @brief dispatches in the correct execution following the node
/// @param node 
/// @return exit_status
int	exec_node(t_node *node)
{
	int	ret;

	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		ret = exec_node_cmd(node);
	else if (node->type == NODE_PIPE)
		ret = exec_pipe(node);
	else if (node->type == NODE_AND)
		ret = exec_and(node);
	else if (node->type == NODE_OR)
		ret = exec_or(node);
	return (ret);
}
