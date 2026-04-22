/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:46:23 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/22 18:06:18 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief will increment 1 to the variable shell level
/// @param tab 
/// @return char ** new value SHLVL
char	**shell_lvl(char **tab)
{
	char	*tmp1;
	char	*tmp2;
	char	**new_tab;
	int		resultat;

	tmp1 = NULL;
	tmp2 = NULL;
	tmp1 = ft_strdup(tab[1]);
	resultat = ft_atoi(tmp1);
	if (!resultat)
		resultat = 0;
	resultat++;
	tmp2 = ft_itoa(resultat);
	new_tab = malloc(sizeof(char *) * 3);
	new_tab[0] = ft_strdup(tab[0]);
	new_tab[1] = ft_strdup(tmp2);
	new_tab[2] = NULL;
	free_tab(tab);
	free(tmp1);
	free(tmp2);
	return (new_tab);
}

/// @brief init the list for env in the form of a linked list
/// @param lst 
/// @param env 
void	init_lst_env(t_list *lst, t_env **env)
{
	char	**tab;
	t_env	*new;

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

/// @brief rebuild env in char ** for the execute cmd
/// @param env 
/// @return 
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
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

/// @brief build the env in char ** when you run the program without the env
/// @param void
/// @return new env
char	**build_env_since_then_nothing(void)
{
	char	**tab;
	char	*tmp;

	tmp =getcwd(NULL, 0);
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
	t_list	*lst = NULL;
	t_env	*lst_env = NULL;
	char	**tab;
	bool	env_build = false;

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
	if (lst == NULL)
		error_message("error when separating the environment\n");
	init_lst_env(lst, &lst_env);
	if (lst_env == NULL)
		error_message("error during the linking of the environment\n");
	ft_lstclear(&lst, free);
	if (env_build)
		free_tab(tab);
	return (lst_env);
}
