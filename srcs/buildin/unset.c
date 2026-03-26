/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:04 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 14:38:13 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_delete_envnode(t_env *preview_node, t_env *node)
{
	preview_node->next = node->next;
	free(node->key_var);
	node->key_var = NULL;
	free(node->var);
	node->var = NULL;
}

// ca fonction mais peut etre faire quelques chose de plus propre, mais en vrai flemme cest deja pas mal
void	buildin_unset(t_command *cmd) // 6
{
	t_env	*tmp;
	t_env	*preview;
	int		len;
	
	len = (ft_strlen(cmd->av[1]) + 1);
	tmp = cmd->shell->env;
	while (tmp)
	{
		if (!ft_strncmp(cmd->av[1], tmp->key_var, len))
		{
			ft_delete_envnode(preview, tmp);
			break;
		}
		// printf("\033[0;35m\033[1mcmd av[0] = {%s}, tmp keyvar = {%s}, tmp var = {%s}, strlen = {%d}\n\033[0m", cmd->av[1], tmp->key_var, tmp->var, i);
		preview = tmp;
		tmp = tmp->next;
	}
	printf_env(cmd->shell->env);
}
