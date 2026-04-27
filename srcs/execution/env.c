/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:46:23 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/27 18:15:26 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief init the list for env in the form of a linked list
/// @param lst 
/// @param env 
static void	init_lst_env(t_list *lst, t_env **env)
{
	char	**tab;
	t_env	*new;

	if (!lst || !env)
		return ;
	while (lst)
	{
		tab = split_in_two(lst->content, '=');
		if (!tab)
			return ;
		if (!ft_strncmp("SHLVL", tab[0], 6))
			tab = shell_lvl(tab);
		new = ft_envnew(tab);
		ft_envadd_back(env, new);
		lst = lst->next;
		free(tab);
	}
}

/// @brief build the env in char ** when you run the program without the env
/// @param void
/// @return new env
static char	**build_env_since_then_nothing(void)
{
	char	**tab;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	tab = malloc(sizeof(char *) * 4);
	tab[0] = ft_strjoin("PWD=", tmp);
	tab[1] = ft_strjoin("SHLVL=", "1");
	tab[2] = ft_strjoin("_=", "/usr/bin/env");
	tab[3] = NULL;
	free(tmp);
	return (tab);
}

/// @brief create a chain list without who will be used 
/// @param env 
/// @return env in list linkend
t_env	*call_env(char **env)
{
	t_list	*lst;
	t_env	*lst_env;
	char	**tab;
	bool	env_build;

	lst = NULL;
	lst_env = NULL;
	env_build = false;
	if (env[0])
		split_tab_to_list(env, &lst);
	else
	{
		tab = build_env_since_then_nothing();
		if (!tab)
			error_message("error when separating the key and var\n");
		env_build = true;
		split_tab_to_list(tab, &lst);
	}
	init_lst_env(lst, &lst_env);
	ft_lstclear(&lst, free);
	if (env_build)
		free_tab(tab);
	return (lst_env);
}
