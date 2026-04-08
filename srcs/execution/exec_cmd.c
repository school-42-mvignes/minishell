/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:41 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/08 13:26:33 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_node *node, char **args, char **envp)
{
	(void)node;
	char	*cmd_path;
	char	*tmp;

	tmp = args[0];
	if (!args || !args[0])
	{
		// free node
		ft_putendl_fd(": command not found", 2);
		node->cmd->shell->exit_status = 127;
		return ;
	}
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd(tmp, 2);
		// free node
		ft_putendl_fd(": command not found", 2);
		node->cmd->shell->exit_status = 127;
		return ;
	}
	execve(cmd_path, args, envp);
	perror(cmd_path);
	free(cmd_path);
	// free node
	node->cmd->shell->exit_status = EXIT_FAILURE;
}
