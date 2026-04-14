/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:05:45 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/14 13:03:16 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief execute the "||" and do a recursive if there are other separators after
/// @param node 
/// @return exit_status
int	exec_or(t_node *node)
{
	int		status;
	pid_t	pid_left;
	pid_t	pid_right;
	
	pid_left = create_fork();
	if (pid_left == 0)
	{
		exec_node(node->left);
		exit(0);
	}
	waitpid(pid_left, &status, 0);
	WEXITSTATUS(status);
	if (!status) // node->cmd->shell->exit_status
	{
		pid_right = create_fork();
		if (pid_right == 0)
		{
			exec_node(node->right);
			exit(0);
		}
		waitpid(pid_right, &status, 0);
	}
	WEXITSTATUS(status);
	return(status);
}
