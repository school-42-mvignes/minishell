/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:40:34 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/30 16:31:42 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_and(t_node *node, t_command *cmd1, t_command *cmd2)
{
	
}
int	exec_or(t_node *node, t_command *cmd1, t_command *cmd2)
{
	
}

void	exec_sec_cmd(t_node *node, t_command *cmd, int pipe[2])
{
	pid_t	pid;

	pid = create_fork();
	if (pid == 0)
		last_child(node, cmd, pipe);
	node->last_pid = pid;
	close(pipe[0]);
	close(pipe[1]);
}

void	exec_first_cmd(t_node *node, int pipe[2])
{
	pid_t	pid;

	create_pipe(pipe);
	pid = create_fork();
	if (pid == 0)
		first_child(node, pipe);
	close(pipe[1]);
}

int	exec_pip(t_node *node, t_command *cmd1, t_command *cmd2)
{
	int		pipe[2];
	int		status;
	int		last_status;
	pid_t	finished_pid;

	exec_first_cmd(cmd1, pipe);
	exec_sec_cmd(node, cmd2, pipe);
	finished_pid = wait(&status);
	if (finished_pid == node->last_pid)
		last_status = status;
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (1);
}

void	what_the_separator(t_node *node, t_shell *shell)
{
	if (node->type == SP_AND)
		shell->exit_status = exec_and(node, node->left->cmd, node->right->cmd);
	else if (node->type == SP_OR)
		shell->exit_status = exec_or(node, node->left->cmd, node->right->cmd);
	else if (node->type == SP_PIPE)
		shell->exit_status = exec_pip(node, node->left->cmd, node->right->cmd);
}
