/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:18:23 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/16 20:24:20 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief open the file and read it
/// @param outfile 
/// @return returns the fd
static int	open_file_in(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("infile");
		return (-1);
	}
	return (fd);
}

/// @brief open the file or create it if it does not exist and read it
/// @param outfile 
/// @return returns the fd
static int	open_file_out(char *outfile)
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

/// @brief Open the file or create it and add it in addition to the existing
/// text and read it
/// @param outfile 
/// @return returns the fd
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

/// @brief Choose how to open the file
/// @param redir 
/// @return returns the fd
int	what_the_outfile(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_IN)
		fd = open_file_in(redir->file);
	else if (redir->type == REDIR_OUT)
		fd = open_file_out(redir->file);
	else if (redir->type == REDIR_APP)
		fd = open_file_app(redir->file);
	else if (redir->type == REDIR_HERE)
		fd = redir->heredoc_fd;	
	return (fd);
}
