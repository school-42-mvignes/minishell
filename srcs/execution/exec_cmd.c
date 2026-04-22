/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:41 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/21 19:04:05 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief writes the correct error message in case of a failure to execute
/// the command
/// @param node 
/// @param str 
void	error_exec_cmd(t_node *node, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
	node->cmd->shell->exit_status = 127;
	free_token_lst(node->cmd->shell->free_the_token);
	free_node(node);
	exit (127);
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
		free_tab(envp);
		error_exec_cmd(node, tmp);
	}
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
	{
		free_tab(envp);
		error_exec_cmd(node, tmp);
	}
	free_token_lst(node->cmd->shell->free_the_token);
	execve(cmd_path, args, envp);
	// if (access(args[0], X_OK) == 0)
	// 	error_exec_cmd(node, tmp);
	perror(cmd_path);
	free(cmd_path);
	free_tab(envp);
	free_node(node);
	exit(126);
}

/// @brief Create and make the redirects of fd for the files called
/// @param redir 
void	create_and_redir_file(t_redir *redir)
{
	int	fd;

	if (redir)
	{
		while (redir)
		{
			fd = what_the_outfile(redir);
			if (fd == -1)
			{
				exit(EXIT_FAILURE);
			}
			if (redir->type == REDIR_IN || redir->type == REDIR_HERE)
				redirect_fd(STDIN_FILENO, fd);
			else
				redirect_fd(STDOUT_FILENO, fd);
			close(fd);
			redir = redir->next;
		}
	}
}

/// @brief executes the command found or buildin in the node command
/// @param node 
/// @return exit_status
int	exec_node_cmd(t_node *node)
{
	pid_t	pid;
	int		status;

	if (exec_without_fork(node))
	{
		exec_buildin_without_fork(node);
		return (node->cmd->shell->exit_status);
	}
	pid = create_fork();
	if (pid == 0)
	{
		create_and_redir_file(node->cmd->redir);
		if (is_one_buildin(node))
			exec_the_buildin(node);
		else
			exec_cmd(node, node->cmd->av, rebuild_env(&node->cmd->shell->env));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		node->cmd->shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		node->cmd->shell->exit_status = 128 + WTERMSIG(status);
	return (node->cmd->shell->exit_status);
}
