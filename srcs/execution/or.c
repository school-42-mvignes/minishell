/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:05:45 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/24 12:04:17 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief execute the "||" and do a recursive if there are other
/// separators after
/// @param node 
/// @return exit_status
int	exec_or(t_node *node)
{
	int	res;

	res = exec_node(node->left);
	if (res != 0)
		res = exec_node(node->right);
	return (res);
}
