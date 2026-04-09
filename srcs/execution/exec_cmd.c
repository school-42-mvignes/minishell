/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:41 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/09 18:36:39 by mvignes          ###   ########.fr       */
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
		exit (127);
	}
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd(tmp, 2);
		// free node
		ft_putendl_fd(": command not found", 2);
		node->cmd->shell->exit_status = 127;
		exit (127);
	}
	execve(cmd_path, args, envp);
	perror(cmd_path);
	free(cmd_path);
	// free node
	node->cmd->shell->exit_status = 126;
	exit(126);
}

void	only_child(t_node *node, int pipefd[2])
{
	int	fd;

	(void)pipefd;
	if (node->cmd->redir)
	{
		fd = what_the_outfile(node->cmd->redir);
		redirect_fd(fd, STDOUT_FILENO);
	}
	// pk ca fonction po
	if (is_one_buildin(node))
		what_the_buildin(node);
	else
		exec_cmd(node, node->cmd->av, rebuild_env(&node->cmd->shell->env));
}

void	exec_simple_cmd(t_node *node, int *pipe)
{
	pid_t	pid;

	create_pipe(pipe);
	pid = create_fork();
	if (pid == 0)
		only_child(node, pipe);
	node->last_pid = pid;
}
