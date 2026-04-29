/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:41 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/29 14:53:47 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief writes the correct error message in case of a failure to execute
/// the command
/// @param node 
/// @param str 
static void	error_exec_cmd(t_shell *shell, char *str, char **env, int exit)
{
	free_tab(env);
	ft_putstr_fd("minishell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	if (exit == 127)
		ft_putendl_fd(": command not found", 2);
	else
	{
		if (access(str, X_OK) != 0)
			ft_putendl_fd(": Permission denied", 2);
		else
			ft_putendl_fd(": Is a directory", 2);
	}
	shell->exit_status = exit;
	exit_free_all(shell->free_the_token, shell->free_the_node, shell, NULL);
}

/// @brief executes the command found
/// @param node 
/// @param args 
/// @param envp 
void	exec_cmd(t_node *node, char **args, char **envp)
{
	char	*cmd_path;
	char	*tmp;

	tmp = args[0];
	if (!args || !args[0] || args[0][0] == '\0')
		error_exec_cmd(node->cmd->shell, tmp, envp, 127);
	cmd_path = find_path(args[0], envp);
	if (!cmd_path)
		error_exec_cmd(node->cmd->shell, tmp, envp, 127);
	execve(cmd_path, args, envp);
	free(cmd_path);
	error_exec_cmd(node->cmd->shell, tmp, envp, 126);
}

/// @brief rebuild env in char ** for the execute cmd
/// @param env 
/// @return char ** env
char	**rebuild_env(t_env **env)
{
	t_env	*tmp;
	char	*str_tmp;
	char	**tab;
	int		i;

	tmp = (*env);
	tab = malloc(sizeof(char *) * (ft_envsize(tmp) + 1));
	i = 0;
	while (tmp)
	{
		str_tmp = ft_strjoin(tmp->key_var, "=");
		tab[i] = ft_strjoin_gnl(str_tmp, tmp->var);
		if (!tab[i])
		{
			free_tab(tab);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

/// @brief exec cmd in child
/// @param node 
static void	child_exec_cmd(t_node *node)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	create_and_redir_file(node, node->cmd->redir);
	if (is_one_buildin(node))
		exec_the_buildin(node, node->cmd->shell);
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

	if (!node->cmd->av[0])
		return (0);
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
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		search_exit_status(node->cmd->shell, status, true);
	}
	return (node->cmd->shell->exit_status);
}
