/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:57 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/18 16:02:49 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief write error export
/// @param cmd 
void	error_export(t_command *cmd)
{
	ft_putstr_fd("minishell: export:", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(cmd->av[1], 2);
	ft_putendl_fd("': not a valid identifier", 2);
	cmd->shell->exit_status = 1;
}

/// @brief create or edit the var in list t_env
/// @param cmd 
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

bool	dont_dash_in_key_var(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		else if (str[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

/// @brief check write env export or create / edit var or error
/// @param cmd 
void	buildin_export(t_command *cmd)
{
	if (!cmd->av[1])
	{
		print_export(cmd->shell->env);
	}
	else
	{
		if ((ft_isalpha(cmd->av[1][0]) || cmd->av[1][0] == '_')
		&& dont_dash_in_key_var(cmd->av[1]))
			create_or_edit_var(cmd);
		else
			error_export(cmd);
	}
}
