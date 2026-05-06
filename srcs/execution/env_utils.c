/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:50:37 by mvignes           #+#    #+#             */
/*   Updated: 2026/05/06 10:13:54 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief incrementing nomber in char
/// @param str 
/// @return char *
static char	*char_incrementing(char *str)
{
	int		res;
	char	*tmp;

	res = ft_atoi(str);
	if (!res)
		res = 0;
	res++;
	tmp = ft_itoa(res);
	return (tmp);
}

/// @brief will increment 1 to the variable shell level
/// @param tab 
/// @return char ** new value SHLVL
char	**shell_lvl(char **tab)
{
	char	**new_tab;

	new_tab = malloc(sizeof(char *) * 3);
	if (!new_tab)
		return (NULL);
	new_tab[0] = ft_strdup(tab[0]);
	if (!new_tab[0])
		return (free_tab(new_tab), NULL);
	new_tab[1] = char_incrementing(tab[1]);
	if (!new_tab[1])
		return (free_tab(new_tab), NULL);
	new_tab[2] = NULL;
	free_tab(tab);
	return (new_tab);
}

/// @brief Function that will create variable which key var and var
/// @param loc 
/// @return t_env, node create
t_env	*create_var(char *key, char *var)
{
	t_env	*new;
	char	**tab;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup(key);
	if (!tab)
		return (free_tab(tab), NULL);
	tab[1] = ft_strdup(var);
	if (!tab)
		return (free_tab(tab), NULL);
	tab[2] = NULL;
	new = ft_envnew(tab);
	if (!new)
		free_tab(tab);
	free(tab);
	new->egal_init = true;
	return (new);
}
