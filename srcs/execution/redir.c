/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:18:23 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/10 10:49:07 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void	exec_redir_in(t_redir *redir, int *pipe)
{
	int		fd;

	if (!redir)
		fd = STDIN_FILENO;
	else
	{
		while (redir)
		{
			fd = what_the_outfile(redir);
			if (fd == -1)
			{
				close(pipe[1]);
				exit(EXIT_FAILURE);
			}
			redir = redir->next;
		}
	}
		redirect_fd(fd, STDIN_FILENO);
		redirect_fd(pipe[1], STDOUT_FILENO);
		close(pipe[0]);
}

void	exec_redir_out(t_node *node, t_command *cmd, t_redir *redir, int *pipe)
{
	int fd;

	if (!redir)
		fd = STDIN_FILENO;
	else
	{
		while (redir)
		{
			fd = what_the_outfile(redir);
			if (fd == -1)
			{
				close(pipe[1]);
				exit(EXIT_FAILURE);
			}
			redir = redir->next;
		}
	}
	edirect_fd(fd, STDOUT_FILENO);
	close(pipe[0]); // mettre dans deuxieme commande
	close(pipe[1]);
} */

int	open_file_in(char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("outfile");
		return (-1);
	}
	return (fd);
}

int	open_file_app(char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("outfile");
		return (-1);
	}
	return (fd);
}

/// @brief 
/// @param redir 
/// @return returns the fd
int	what_the_outfile(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_IN) // action redir in
		fd = open_file_in(redir->file);
	else if (redir->type == REDIR_OUT) // action redir out
		fd = open_file_in(redir->file);
	else if (redir->type == REDIR_APP) // action redir app
		fd = open_file_app(redir->file);
	// else if (cmd->redir->type == REDIR_HERE) // action redir here doc
		// Relancer un minishell (donc avoir un minishell dans le main)

	// redirect_fd(NULL, fd);
	// printf("%i", fd);
	return (fd);
}
