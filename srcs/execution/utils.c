/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:04:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/13 20:35:14 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief check if he’s a buildin
/// @param node 
/// @return true or false
bool	is_one_buildin(t_node *node)
{
	if (!ft_strncmp(ECHO, node->cmd->av[0], 5)
		|| !ft_strncmp(CD, node->cmd->av[0], 3)
		|| !ft_strncmp(PWD, node->cmd->av[0], 4)
		|| !ft_strncmp(ENV, node->cmd->av[0], 4)
		|| !ft_strncmp(EXPORT, node->cmd->av[0], 7)
		|| !ft_strncmp(UNSET, node->cmd->av[0], 6)
		|| !ft_strncmp(EXIT, node->cmd->av[0], 5))
		return (true);
	return (false);
}

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

/// @brief Use dup2 = Duplicate new_fd to old_fd and close old_fd and exit in case of a problem
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

/// @brief search last redir for execution in the good redirection
/// @param redir 
/// @return last redir
t_redir	*search_last_fd_redir(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
