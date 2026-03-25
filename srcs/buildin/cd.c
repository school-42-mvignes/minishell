/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:44 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 14:37:06 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buildin_cd(t_command *cmd) // 2
{
	t_env	*pwd;
	t_env	*last_pwd;

	pwd = search_key_var(cmd->shell->env, "PWD");
	if (!pwd)
		return ;
	if (chdir(cmd->av[1]))
	{
		printf("OUI OUI BAGUETTE NOT A DIRECTORY\n");
		last_pwd = NULL;
		exit(1);
	}
	last_pwd = search_key_var(cmd->shell->env, "PWD");
	if (!last_pwd)
		return ;
	free(last_pwd->var);
	last_pwd->var = pwd->var;
	char	*buffer;
	
	getcwd(buffer, 4096);
	pwd->var = buffer;
	
	
	
	
	
	printf_env(cmd->shell->env);
}