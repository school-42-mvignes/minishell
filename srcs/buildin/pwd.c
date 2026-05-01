/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:01 by mvignes           #+#    #+#             */
/*   Updated: 2026/05/01 09:37:30 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_getcwd(t_shell *shell, char *str, bool pwd, bool first)
{
	char	*para;
	char	*msg;

	free(str);
	if (first)
	{
		if (pwd)
			para = ft_strdup("pwd: ");
		else
			para = ft_strdup("chdir: ");
		msg = ft_strjoin_gnl(para, "error retrieving current directory: getcwd: ");
		msg = ft_strjoin_gnl(msg, "cannot access parent directories:");
		msg = ft_strjoin_gnl(msg, " No such file or directory");
		ft_putendl_fd(msg, 2);
		free(msg);
	}
	shell->exit_status = 1;
	if (shell->forking)
		exit_free_all(shell->free_the_token, shell->free_the_node, shell, NULL);
}

/// @brief write path or the message error
/// @param cmd 
void	buildin_pwd(t_command *cmd)
{
	t_env	*pwd;
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		error_getcwd(cmd->shell, path, true, true);
	pwd = search_key_var(cmd->shell->env, "PWD", false);
	if (!pwd)
	{
		pwd = create_var("PWD", path);
		if (!pwd)
			return ;
		ft_envadd_back(&cmd->shell->env, pwd);
		ft_putendl_fd(pwd->var, 1);
	}
	if (path)
		ft_putendl_fd(path, 1);
	// else
	// {
	// 	ft_putstr_fd("error retrieving current directory: getcwd: cannot", 2);
	// 	error_message(" access parent directories: No such file or directory");
	// }
	free(path);
}
