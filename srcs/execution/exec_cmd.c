/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:41 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 18:12:16 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(char **args, char **envp)
{
	char	*cmd_path;
	char	*tmp;

	tmp = args[0];
	if (!args || !args[0])
	{
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd(tmp, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror(cmd_path);
	free(cmd_path);
	exit(EXIT_FAILURE);
}
