/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:41 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/13 23:31:53 by mvignes          ###   ########.fr       */
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
		// printf("qweqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");

		// free node
		ft_putendl_fd(": command not found", 2);
		node->cmd->shell->exit_status = 127;
		exit (127);
	}
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		// printf("qweqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");

		ft_putstr_fd(tmp, 2);
		// free node
		ft_putendl_fd(": command not found", 2);
		node->cmd->shell->exit_status = 127;
		exit (127);
	}
	// printf("%s\n\n\n\n", args[0]);
	execve(cmd_path, args, envp);
	// printf("qweqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");

	perror(cmd_path);
	free(cmd_path);
	// free node
	node->cmd->shell->exit_status = 126;
	exit(126);
}

void	only_child(t_node *node)
{
	int	fd;

	fd = STDIN_FILENO;
	if (node->cmd->redir)
	{
		// printf("qweqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");
		fd = what_the_outfile(node->cmd->redir);
		redirect_fd(STDOUT_FILENO, fd);
	}
	// pk ca fonction po
	if (is_one_buildin(node))
		what_the_buildin(node);
	else
		exec_cmd(node, node->cmd->av, rebuild_env(&node->cmd->shell->env));
}

void	exec_node_cmd(t_node *node) // exec node cmd
{
	pid_t	pid;
	int		status;

	pid = create_fork();
	if (pid == 0)
		only_child(node);
	waitpid(pid, &status, 0);
	// node->last_pid = pid;
}
