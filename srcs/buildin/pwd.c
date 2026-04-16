/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:01 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/16 14:35:47 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buildin_pwd(t_command *cmd)
{
	t_env	*tmp;

	tmp = cmd->shell->env;
	while (ft_strncmp("PWD", tmp->key_var, 4))
		tmp = tmp->next;
	if (!ft_strncmp("PWD", tmp->key_var, 4))
		ft_putendl_fd(tmp->var, 1);
}

/* void	buildin_pwd(t_command *cmd)
{
	
} */
