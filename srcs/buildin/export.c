/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:57 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/16 14:46:35 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_export(t_command *cmd)
{
	ft_putstr_fd("minishell: export:", 1);
	ft_putchar_fd('`', 1);
	ft_putstr_fd(cmd->av[1], 1);
	ft_putendl_fd("': not a valid identifier", 1);
}

void	create_or_edit_var(t_command *cmd)
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
}

void	buildin_export(t_command *cmd)
{
	if (!cmd->av[1])
	{
		printf_export(cmd->shell->env);
	}
	else
	{
		if (!ft_isalnum(cmd->av[1][0]) || cmd->av[1][0] == '_')
			create_or_edit_var(cmd);
		else
			error_export(cmd);
	}
}
