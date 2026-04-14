/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:40:34 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/13 16:50:19 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	i = 0;

/* static int	exec_and(t_node *node, t_command *cmd1, t_command *cmd2)
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
} */
/* 
static int	exec_pipe(t_node *node)
{
	int		pipe[2];
	pid_t	pid;
	int		status;
	int		last_status;
	pid_t	finished_pid;

	pid = create_fork();
	if (pid == 0)
	{
		what_the_separator(node, pipe);
	}
	while (finished_pid != node->last_pid)
	{
		finished_pid = wait(&status);
		if (finished_pid == node->last_pid)
			last_status = status;
	}
	close(pipe[1]);
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (1);

}
 */
/* static void	wait_decision(t_node *node)
{
	pid_t	pid;
	int		status;
	// int		last_status;
	pid_t	finished_pid;

	pid = create_fork();
	if (pid == 0)
	{
		if (node->type == NODE_PIPE)
			exec_pipe(node);
		else if (node->type == NODE_AND)
			exec_and(node, node->left->cmd, node->right->cmd);
		else if (node->type == NODE_OR)
			exec_or(node, node->left->cmd, node->right->cmd);
	}
	while (finished_pid != node->last_pid)
	{
		finished_pid = wait(&status);
		if (finished_pid == node->last_pid)
		{
			// last_status = status;
			printf("JE SUIS PAASSSER LA, j'ai bien wait\n\n");
		}
	}
	// if (WIFEXITED(last_status))
	// {
	// 	return (WEXITSTATUS(last_status));
	// 	printf("last_status = %i\n\n", WEXITSTATUS(last_status));
	// }
	// return (1);
	// printf("exit_status === %i", node->cmd->shell->exit_status);
} */

/* int	what_the_separator(t_node *node, int *pipe) // revoir la fonction car s il y a un pipe apres un separateur cela peut faire bugger
{
	pid_t	pid;
	int		status;
	int		last_status;
	pid_t	finished_pid;

	pid = create_fork();
	if (pid == 0)
	{
		if (node->type == NODE_PIPE)
			exec_pipe(node);
		else if (node->type == NODE_AND)
			exec_and(node, node->left->cmd, node->right->cmd);
		else if (node->type == NODE_OR)
			exec_or(node, node->left->cmd, node->right->cmd);
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

void	what_the_first_separator(t_node *node) // revoir la fonction car s il y a un pipe apres un separateur cela peut faire bugger
{
	// pid_t	pid;
	// int		status;
	// int		last_status;
	// pid_t	finished_pid;


	if (node->type == NODE_CMD)
		exec_simple_cmd(node);
	else if (node->type == NODE_PIPE)
		exec_pipe(node);
	else if (node->type == NODE_AND)
		exec_and(node, node->left->cmd, node->right->cmd);
	else if (node->type == NODE_OR)
		exec_or(node, node->left->cmd, node->right->cmd);
	// if (WIFEXITED(last_status))
	// {
	// 	return (WEXITSTATUS(last_status));
	// 	printf("last_status = %i\n\n", WEXITSTATUS(last_status));
	// }
	// return (1);
	// printf("exit_status === %i", node->cmd->shell->exit_status);
} */
// cat -e > Makefile | cat -e | cat -e | grep printf > test
