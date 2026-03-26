/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:44 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 19:03:48 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buildin_cd(t_command *cmd)
{
	t_env	*pwd;
	t_env	*last_pwd;
	char	*new_localisation;

	pwd = search_key_var(cmd->shell->env, "PWD");
	if (!pwd)
		return ;
	if (chdir(cmd->av[1]))
	{
		printf("OUI OUI BAGUETTE NOT A DIRECTORY\n");
		pwd = NULL;
		exit(1); // dire pas bon sans quitter
	}
	last_pwd = search_key_var(cmd->shell->env, "OLDPWD");
	if (!last_pwd)
		return ;
	free(last_pwd->var);
	last_pwd->var = pwd->var;
	new_localisation =  getcwd(NULL, 0);
	pwd->var = new_localisation;	
	// printf_env(cmd->shell->env);
}
