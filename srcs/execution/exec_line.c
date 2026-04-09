/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:27:15 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/09 17:19:52 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_line(t_node *node)
{
	int		pipe[2];
	int		status;
	int		last_status;
	pid_t	finished_pid;

	if (node->type == NODE_CMD)
	{
		exec_simple_cmd(node, pipe);
	}
	else
	{
		what_the_separator(node, pipe);
	}
	while (finished_pid != node->last_pid)
	{
		finished_pid = wait(&status);
		if (finished_pid == node->last_pid)
			last_status = status;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (1);
}
