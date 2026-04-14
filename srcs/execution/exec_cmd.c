/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:41 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/14 11:11:09 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_exec_cmd(t_node *node, char *str)
{
	if (str)
		ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
	node->cmd->shell->exit_status = 127;
	exit (127);
}

void	exec_cmd(t_node *node, char **args, char **envp) // quitte pas bien quand error 127
{
	(void)node;
	char	*cmd_path;
	char	*tmp;

	tmp = args[0];
	if (!args || !args[0])
		error_exec_cmd(node, tmp);
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
		error_exec_cmd(node, tmp);
	execve(cmd_path, args, envp);
	perror(cmd_path);
	free(cmd_path);
	// free node
	node->cmd->shell->exit_status = 126;
	exit(126);
}

void	only_child(t_node *node)
{
	if (is_one_buildin(node))
		what_the_buildin(node);
	else
		exec_cmd(node, node->cmd->av, rebuild_env(&node->cmd->shell->env));
}

void	create_and_redir_file(t_redir *redir)
{
	if (redir)
	{
		while (redir)
		{
			redir->file_fd = what_the_outfile(redir);
			if (redir->file_fd == -1)
			{
				exit(EXIT_FAILURE);
			}
			redir = redir->next;
		}
		redirect_fd(redir->file_fd, STDIN_FILENO);
	}
}

void	exec_node_cmd(t_node *node)
{
	pid_t	pid;
	int		status;

	pid = create_fork();
	if (pid == 0)
	{
		create_and_redir_file(node->cmd->redir);
		only_child(node);
	}
	waitpid(pid, &status, 0);
}
