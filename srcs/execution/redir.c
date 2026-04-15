/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:18:23 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/15 14:58:28 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_file_in(char *outfile)
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

static int	open_file_app(char *outfile)
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

	fd = -1;
	if (redir->type == REDIR_IN) // action redir in
		fd = open_file_in(redir->file);
	else if (redir->type == REDIR_OUT) // action redir out
		fd = open_file_in(redir->file);
	else if (redir->type == REDIR_APP) // action redir app
		fd = open_file_app(redir->file);
	else if (redir->type == REDIR_HERE)
		fd = redir->heredoc_fd;	
	return (fd);
}