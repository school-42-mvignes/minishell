/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:44 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/07 16:11:57 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buildin_cd(t_command *cmd)
{
	t_env	*pwd;
	t_env	*last_pwd;
	t_env	*home;
	char	*new_localisation;

	home = NULL;
	pwd = search_key_var(cmd->shell->env, "PWD");
	if (!pwd)
		return ;
	if (cmd->av[1] == NULL)
		buildin_cd_cut(cmd, home);
	else if (chdir(cmd->av[1]))
	{
		pwd = NULL;
		return ;
	}
	last_pwd = search_key_var(cmd->shell->env, "OLDPWD");
	if (!last_pwd)
		return ;
	free(last_pwd->var);
	last_pwd->var = pwd->var;
	new_localisation =  getcwd(NULL, 0);
	pwd->var = new_localisation;	
}

void	buildin_cd_cut(t_command *cmd, t_env *home)
{
	home = search_key_var(cmd->shell->env, "HOME");
	if (home == NULL)
	{
		write(2, "HOME not set\n", 12);
		return ;
	}
	chdir(home->var);
}