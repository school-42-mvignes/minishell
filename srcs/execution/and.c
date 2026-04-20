/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:05:23 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/16 14:49:28 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief execute the "&&" and do a recursive if there
/// are other separators after
/// @param node 
/// @return exit_status
int	exec_and(t_node *node)
{
	int	res;

	res = exec_node(node->left);
	if (res == 0)
		res = exec_node(node->right);
	return (res);
}
