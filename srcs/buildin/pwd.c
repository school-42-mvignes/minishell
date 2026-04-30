/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:01 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/30 14:36:26 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief write path or the message error
/// @param cmd 
void	buildin_pwd(t_command *cmd)
{
	t_env	*pwd;
	char	*path;

	path = getcwd(NULL, 0);
	pwd = search_key_var(cmd->shell->env, "PWD", false);
	if (!pwd)
	{
		pwd = create_var("PWD", path);
		if (!pwd)
			return ;
		ft_envadd_back(&cmd->shell->env, pwd);
		ft_putendl_fd(pwd->var, 1);
	}
	if (pwd)
		ft_putendl_fd(pwd->var, 1);
	else
	{
		ft_putstr_fd("error retrieving current directory: getcwd: cannot", 2);
		error_message(" access parent directories: No such file or directory");
	}
	free(path);
}
