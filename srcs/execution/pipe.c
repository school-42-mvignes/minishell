/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:54:22 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/09 18:52:46 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_sec_cmd(t_node *node, t_command *cmd, int pipe[2])
{
	pid_t	pid;
	int		fd;
	t_redir	*redir;

	pid = create_fork();
	if (pid == 0)
	{
		close(pipe[1]);
		redirect_fd(pipe[0], STDIN_FILENO);
		if (!cmd->redir)
			fd = STDIN_FILENO;
		else
		{
			redir = search_last_fd_redir(cmd->redir);
			fd = what_the_outfile(redir);
			if (fd == -1)
			{
				close(pipe[0]);
				// free_all(pipex);
				exit(EXIT_FAILURE);
			}
			redirect_fd(fd, STDOUT_FILENO);
		}

		exec_cmd(node, cmd->av, rebuild_env(&cmd->shell->env));
	}
	node->last_pid = pid;
	close(pipe[0]);
	close(pipe[1]);
}

void	exec_first_cmd(t_node *node, t_command *cmd, int pipe[2])
{
	pid_t	pid;
	int		fd;

	create_pipe(pipe);
	pid = create_fork();
	if (pid == 0)
	{

		if (!cmd->redir)
			fd = STDIN_FILENO;
		else
			fd = what_the_outfile(cmd->redir);
		close(pipe[0]);
		if (fd == -1)
		{
			// free_all(pipex);
			close(pipe[1]);
			exit(EXIT_FAILURE);
		}
		redirect_fd(fd, STDIN_FILENO);
		redirect_fd(pipe[1], STDOUT_FILENO);
		close(pipe[0]);
		exec_cmd(node, cmd->av, rebuild_env(&cmd->shell->env));
	}
	close(pipe[1]);
}
