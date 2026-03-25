/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:01 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 14:37:37 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	buildin_pwd(t_command *cmd) // 4
{
	t_env	*tmp;

	tmp = cmd->shell->env;
	while (ft_strncmp("PWD", tmp->key_var, 4))
		tmp = tmp->next;
	if (!ft_strncmp("PWD", tmp->key_var, 4))
		ft_putendl_fd(tmp->var, 1);				// mettre dans un buffer
}
