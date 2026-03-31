/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:18:23 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/31 14:02:11 by mvignes          ###   ########.fr       */
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
	printf("%i", fd);
	return (fd);
}
