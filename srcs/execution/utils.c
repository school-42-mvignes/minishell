/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:04:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/27 18:17:19 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief create new pipe and exit in case of a problem
/// @param pipefd 
/// @return if there is an error during the creation
int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

/// @brief create new fork and exit in case of a problem
/// @param  
/// @return the pid
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

/// @brief Use dup2 = Duplicate new_fd to old_fd and close old_fd and exit
/// in case of a problem
/// @param old_fd
/// @param new_fd 
void	redirect_fd(int old_fd, int new_fd)
{
	if (dup2(new_fd, old_fd) == -1)
	{
		perror("dup2");
		exit(1);
	}
}
