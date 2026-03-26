/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:18:23 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 20:16:58 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	redirect_fd(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(old_fd);
}

void	what_the_outfile(t_command *cmd)
{
	int	fd;

	if (cmd->redir->token == REDIR_IN) // action redir in
		fd = open_file_in(cmd->redir->file);
	else if (cmd->redir->token == REDIR_OUT) // action redir out
		fd = open_file_in(cmd->redir->file);
	else if (cmd->redir->token == REDIR_APP) // action redir app
		fd = open_file_app(cmd->redir->file);
	// else if (cmd->redir->token == REDIR_HERE) // action redir here doc
		// Relancer un minishell (donc avoir un minishell dans le main)
}