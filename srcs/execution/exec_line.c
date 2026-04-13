/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:27:15 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/13 20:06:45 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_node(t_node *node);

static void	exec_redir_in(t_redir *redir, int *pipe)
{
	int		fd;

	if (redir)
	{
		while (redir)
		{
			fd = what_the_outfile(redir);
			if (fd == -1)
			{
				close(pipe[0]);
				exit(EXIT_FAILURE);
			}
			redir = redir->next;
		}
		redirect_fd(STDIN_FILENO, fd);
	}
	redirect_fd(pipe[0], STDOUT_FILENO);
}

void	exec_redir_out(t_redir *redir, int *pipe)
{
	(void)redir;
	int fd;

	close(pipe[1]);
	redirect_fd(pipe[1], STDIN_FILENO);
	if (redir)
	{
		while (redir)
		{
			fd = what_the_outfile(redir);
			if (fd == -1)
			{
				close(pipe[0]);
				exit(EXIT_FAILURE);
			}
			redir = redir->next;
		}
		redirect_fd(STDOUT_FILENO, fd);
	}
}

static int	exec_pipe(t_node *node)
{
	int		pipe[2];
	int		status;
	pid_t	pid_left;
	pid_t	pid_right;
	
	if (create_pipe(pipe))
		printf("Probleme pendant la creation du pipe\n");
	pid_left = create_fork();
	if (pid_left == 0)
	{
		exec_redir_in(node->left->cmd->redir, pipe);
		exec_node(node->left);
		close(pipe[1]);
	}
	pid_right = create_fork();
	if (pid_right == 0)
	{
		exec_redir_out(node->right->cmd->redir, pipe);
		exec_node(node->right);
		close(pipe[0]);
		close(pipe[1]);
	}
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	WEXITSTATUS(status);
	return(status);
}

void	exec_node(t_node *node)
{
	if (node->type == NODE_CMD)
		exec_node_cmd(node);
	else if (node->type == NODE_PIPE)
		exec_pipe(node);
	// else if (node->type == NODE_AND)
	// 	exec_and(node, node->left->cmd, node->right->cmd);
	// else if (node->type == NODE_OR)
	// 	exec_or(node, node->left->cmd, node->right->cmd);
}


int	exec_line(t_node *node)
{
	exec_node(node);
	return (1);
}
