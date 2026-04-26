/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 10:21:13 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/26 10:27:20 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief wait exit status
/// @param node 
/// @param status 
void	search_exit_status(t_shell *shell, int status, bool loc)
{
	if (loc)
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		signal(SIGINT, controller);
		signal(SIGQUIT, SIG_IGN);
	}
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

/// @brief write message error
/// @param message 
void	error_message(char *message)
{
	ft_putendl_fd(message, 2);
	exit (1);
}

t_shell	*call_shell(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while (!tmp->cmd)
		tmp = tmp->right;
	if (!tmp->cmd->shell)
		return (NULL);
	return (tmp->cmd->shell);
}
