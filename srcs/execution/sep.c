/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:40:34 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/08 12:06:13 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_and(t_node *node, t_command *cmd1, t_command *cmd2)
{
	(void)node;
	(void)cmd1;
	(void)cmd2;
	printf("PAS ENCORE FAIT\n");
	return (1);
}
static int	exec_or(t_node *node, t_command *cmd1, t_command *cmd2)
{
	(void)node;
	(void)cmd1;
	(void)cmd2;
	printf("PAS ENCORE FAIT\n");
	return (1);
}

static int	exec_simple_cmd(t_node *node)
{
	int		status;
	int		last_status;
	pid_t	finished_pid;
	pid_t	pid;

	pid = create_fork();
	if (pid == 0)
		exec_cmd(node, node->cmd->av, rebuild_env(&node->cmd->shell->env));
	finished_pid = wait(&status);
	if (finished_pid == node->last_pid)
		last_status = status;
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (1);
}

static int	exec_pip(t_node *node, t_command *cmd1, t_command *cmd2)
{
	int		pipe[2];
	int		status;
	int		last_status;
	pid_t	finished_pid;

	exec_first_cmd(node, cmd1, pipe);
	exec_sec_cmd(node, cmd2, pipe);
	finished_pid = wait(&status);
	if (finished_pid == node->last_pid)
		last_status = status;
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (1);
}

void	what_the_separator(t_node *node, t_shell *shell) // revoir la fonction car s il y a un pipe apres un separateur cela peut faire bugger
{
	(void)shell;
	int		exit;	//shell->exit_status

	if (node->type == NODE_CMD)
		// exit = what_the_buildin(node);
		exit = exec_simple_cmd(node);
	if (node->type == NODE_PIPE)
		exit = exec_pip(node, node->left->cmd, node->right->cmd);
	else if (node->type == NODE_AND)
		exit = exec_and(node, node->left->cmd, node->right->cmd);
	else if (node->type == NODE_OR)
		exit = exec_or(node, node->left->cmd, node->right->cmd);
	printf("exit = %i\n", shell->exit_status);
	(void)exit;
}

