/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:41 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/24 10:32:00 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief writes the correct error message in case of a failure to execute
/// the command
/// @param node 
/// @param str 
void	error_exec_cmd(t_node *node, char *str, char **env, bool status)
{
	int	exit_status;

	free_tab(env);
	exit_status = 126;
	if (status)
		exit_status = 127;
	ft_putstr_fd("minishell: line 1: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
	node->cmd->shell->exit_status = exit_status;
	exit_free_all(node->cmd->shell->free_the_token,
		node->cmd->shell->free_the_node, node->cmd->shell, NULL);
}

/// @brief executes the command found
/// @param node 
/// @param args 
/// @param envp 
void	exec_cmd(t_node *node, char **args, char **envp)
{
	(void)node;
	char		*cmd_path;
	char		*tmp;

	tmp = args[0];
	if (!args || !args[0])
	{
		error_exec_cmd(node, tmp, envp, true);
	}
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		error_exec_cmd(node, tmp, envp, true);
	}
	execve(cmd_path, args, envp);
	free(cmd_path);
	error_exec_cmd(node, tmp, envp, false);
}

/// @brief exec cmd in child
/// @param node 
static void	child_exec_cmd(t_node *node)
{
	create_and_redir_file(node->cmd->redir);
	if (is_one_buildin(node))
		exec_the_buildin(node);
	else
		exec_cmd(node, node->cmd->av, rebuild_env(&node->cmd->shell->env));
}

/// @brief executes the command found or buildin in the node command
/// @param node 
/// @return exit_status
int	exec_node_cmd(t_node *node)
{
	pid_t	pid;
	int		status;

	if (node->cmd->av[1])
		if (is_wildcard(node->cmd->av[1]))
			node->cmd->av = exec_wildcard(node->cmd->av);
	if (exec_without_fork(node))
		exec_buildin_without_fork(node);
	else
	{
		pid = create_fork();
		if (pid == 0)
			child_exec_cmd(node);
		waitpid(pid, &status, 0);
		search_exit_status(node->cmd->shell, status);
	}
	return (node->cmd->shell->exit_status);
}
