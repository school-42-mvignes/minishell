/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:41 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/08 20:07:37 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_node *node, char **args, char **envp) // quitte pas bien quand error 127
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

void	exec_simple_cmd(t_node *node) // les forks sorte mal
{
	int		status;
	// int		last_status;
	// pid_t	finished_pid;
	pid_t	pid;

	pid = create_fork();
	if (pid == 0)
		exec_cmd(node, node->cmd->av, rebuild_env(&node->cmd->shell->env));
	wait(&status);
	// finished_pid = wait(&status);
	// if (finished_pid == node->last_pid)
	// 	last_status = status;
	// if (WIFEXITED(last_status))
	// 	node->cmd->shell->exit_status = last_status;
		// return (WEXITSTATUS(last_status));
	// return ;
}
