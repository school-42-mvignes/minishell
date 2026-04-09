/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:04:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/09 18:46:11 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	redirect_fd(int new_fd, int old_fd)
{
	if (dup2(new_fd, old_fd) == -1)
	{
		perror("dup2");
		exit(1);
	}
}

t_redir	*search_last_fd_redir(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
