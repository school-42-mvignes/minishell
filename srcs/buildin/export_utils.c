/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 16:13:08 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/30 16:30:00 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief create node var empty for export
/// @param cmd 
static t_env	*create_node_var_empty(char *av)
{
	t_env	*new;
	char	**tab;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup(av);
	if (!tab)
		return (free_tab(tab), NULL);
	tab[1] = ft_strdup("");
	if (!tab)
		return (free_tab(tab), NULL);
	tab[2] = NULL;
	new = ft_envnew(tab);
	if (!new)
		free_tab(tab);
	free(tab);
	new->egal_init = false;
	return (new);
}

/// @brief create or modif var empty var
/// @param av 
/// @param node 
/// @param env 
void	empty_var(char *av, t_env *node, t_env *env)
{
	node = search_key_var(env, av, false);
	if (node)
	{
		if (node->var)
		{
			free(node->var);
			node->var = ft_strdup("");
			return ;
		}
	}
	node = create_node_var_empty(av);
	if (!node)
		return ;
	ft_envadd_back(&env, node);
}
