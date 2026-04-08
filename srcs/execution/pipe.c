/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:54:22 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/08 11:48:42 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file_read(char *infile)
{
	int	fd;

	printf("JE SUIS PASSER PAR ICI\n");
	fd = open(infile, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("open infile");
		return (-1);
	}
	return (fd);
}

int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

pid_t	create_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

void	redirect_fd(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(old_fd);
}

t_redir	*search_last_fd_redir(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	exec_sec_cmd(t_node *node, t_command *cmd, int pipe[2])
{
	pid_t	pid;
	t_redir	*redir;

	pid = create_fork();
	if (pid == 0)
	{
		printf("proubleme la\n");
		printf("infile error = %s\n\n\n", cmd->redir->file);

		close(pipe[1]);
		redirect_fd(pipe[0], STDIN_FILENO);
		redir = search_last_fd_redir(cmd->redir);
		redir->file_fd = what_the_outfile(redir);
		if (redir->file_fd == -1)
		{
			close(pipe[0]);
			// free_all(pipex);
			// exit(EXIT_FAILURE);
		}
		redirect_fd(redir->file_fd, STDOUT_FILENO);
		exec_cmd(node, cmd->av, rebuild_env(&cmd->shell->env));
	}
	// last_child(node, cmd, pipe);
	node->last_pid = pid;
	close(pipe[0]);
	close(pipe[1]);
}

void	exec_first_cmd(t_node *node, t_command *cmd, int pipe[2])
{
	pid_t	pid;

	create_pipe(pipe);
	pid = create_fork();
	if (pid == 0)
	{
		printf("proubleme ici\n");
		// printf("av[0] = %s\n\n\n", cmd->av[0]);
		// printf("infile error = %d\n\n\n", cmd->redir->file_fd);
		printf("infile error = %s\n\n\n", cmd->redir->file);
		cmd->redir->file_fd = open_file_read(cmd->redir->file);
		close(pipe[0]);
		if (cmd->redir->file_fd == -1)
		{
			// free_all(pipex);
			close(pipe[1]);
			// exit(EXIT_FAILURE);
		}
		redirect_fd(cmd->redir->file_fd, STDIN_FILENO);
		redirect_fd(pipe[1], STDOUT_FILENO);
		close(pipe[0]);
		exec_cmd(node, cmd->av, rebuild_env(&cmd->shell->env));
	}
	close(pipe[1]);
}
