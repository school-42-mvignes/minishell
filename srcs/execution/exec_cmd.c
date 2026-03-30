/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:41 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/30 19:21:32 by mvignes          ###   ########.fr       */
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
		exit(127);
	}
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd(tmp, 2);
		// free node
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror(cmd_path);
	free(cmd_path);
	// free node
	exit(EXIT_FAILURE);
}
