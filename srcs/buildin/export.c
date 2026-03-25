/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:57 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 14:37:49 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buildin_export(t_command *cmd) // 5 // a tester quand on aura un minishell avec readline
{
	t_env	*node;
	char	**tab;

	tab = split_in_two(cmd->av[1], '=');
	if (!tab)
		return ;
	node = search_key_var(cmd->shell->env, tab[0]);
	if (!node)
	{
		node = ft_envnew(tab);
		ft_envadd_back(&cmd->shell->env, node);
		free(tab);
	}
	else
	{
		free(tab[0]);
		free(node->var);
		node->var = NULL;
		node->var = tab[1];
		free(tab);
	}
	printf_env(cmd->shell->env);
}
