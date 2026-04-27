/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:44 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/25 12:12:13 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	error_cd(t_command *cmd)
{
	if (!cmd->av[1] || cmd->av[1][0] == '\0')
	{
		cmd->shell->exit_status = 0;
		return (true);
	}
	if (cmd->av[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		cmd->shell->exit_status = 1;
		return (true);
	}
	return (false);
}

static t_env	*create_last_pwd(char *loc)
{
	t_env	*new;
	char	**tab;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup("OLDPWD");
	if (!tab)
		return (free_tab(tab), NULL);
	tab[1] = ft_strdup(loc);
	if (!tab)
		return (free_tab(tab), NULL);
	tab[2] = NULL;
	new = ft_envnew(tab);
	if (!new)
		free_tab(tab);
	return (new);
}

static void	edit_last_pwd(t_env *env, t_env *pwd)
{
	t_env	*last_pwd;
	char	*new_localisation;

	new_localisation = getcwd(NULL, 0);
	last_pwd = search_key_var(env, "OLDPWD");
	if (!last_pwd)
	{
		last_pwd = create_last_pwd(new_localisation);
		if (!last_pwd)
			return ;
		ft_envadd_back(&env, last_pwd);
	}
	free(last_pwd->var);
	last_pwd->var = pwd->var;
	pwd->var = new_localisation;
}

void	buildin_cd(t_command *cmd)
{
	t_env	*pwd;
	t_env	*home;

	if (error_cd(cmd))
		return ;
	home = NULL;
	pwd = search_key_var(cmd->shell->env, "PWD");
	if (!pwd)
		return ;
	if (cmd->av[1] == NULL)
		buildin_cd_cut(cmd, home);
	else if (chdir(cmd->av[1]))
	{
		pwd = NULL;
		cmd->shell->exit_status = 1;
		return ;
	}
	edit_last_pwd(cmd->shell->env, pwd);
}

void	buildin_cd_cut(t_command *cmd, t_env *home)
{
	home = search_key_var(cmd->shell->env, "HOME");
	if (home == NULL)
	{
		write(2, "HOME not set\n", 13);
		return ;
	}
	chdir(home->var);
}
