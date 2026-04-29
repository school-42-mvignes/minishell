/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:44 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/29 14:32:50 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief check if there are any errors
/// @param cmd 
/// @return bool true == error
static bool	error_cd(t_command *cmd)
{
	if (cmd->av[1])
	{
		if (cmd->av[1][0] == '\0')
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
	}
	return (false);
}

/// @brief Function that will edit the pwd of the already existing variable
/// @param env 
/// @param pwd 
static void	edit_pwd(t_env *env, t_env *node_env_pwd)
{
	char	*new_localisation;

	new_localisation = getcwd(NULL, 0);
	if (!node_env_pwd)
	{
		node_env_pwd = create_var("PWD", new_localisation);
		if (!node_env_pwd)
			return ;
		free(new_localisation);
		ft_envadd_back(&env, node_env_pwd);
		return ;
	}
	else
	{
		if (node_env_pwd->var)
			free(node_env_pwd->var);
		node_env_pwd->var = new_localisation;
	}
}

/// @brief Function that will edit the last pwd of the already existing variable
/// @param env 
/// @param pwd 
static void	edit_last_pwd(t_env *env, t_env *node_env_pwd)
{
	t_env	*last_pwd;

	last_pwd = search_key_var(env, "OLDPWD");
	if (!last_pwd)
	{
		last_pwd = create_var("OLDPWD", node_env_pwd->var);
		if (!last_pwd)
			return ;
		ft_envadd_back(&env, last_pwd);
	}
	else
	{
		free(last_pwd->var);
		last_pwd->var = ft_strdup(node_env_pwd->var);
	}
}

/// @brief Function that redirection to the home
/// @param cmd 
/// @param home 
static void	redirection_to_the_home(t_command *cmd)
{
	t_env	*home;

	home = search_key_var(cmd->shell->env, "HOME");
	if (home == NULL)
	{
		write(2, "HOME not set\n", 13);
		return ;
	}
	chdir(home->var);
}

/// @brief Function that distributes the work for the different CD actions
/// @param cmd 
void	buildin_cd(t_command *cmd)
{
	t_env	*pwd;

	if (error_cd(cmd))
		return ;
	pwd = search_key_var(cmd->shell->env, "PWD");
	if (!pwd)
		return ;
	if (cmd->av[1] == NULL)
		redirection_to_the_home(cmd);
	else if (chdir(cmd->av[1]))
	{
		write(2, "Minishell: cd: ", 16);
		ft_putstr_fd(cmd->av[1], 2);
		ft_putendl_fd(": Not a directory", 2);
		pwd = NULL;
		cmd->shell->exit_status = 1;
		return ;
	}
	edit_last_pwd(cmd->shell->env, pwd);
	edit_pwd(cmd->shell->env, pwd);
	cmd->shell->exit_status = 0;
}
