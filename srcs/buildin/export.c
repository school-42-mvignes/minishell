/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:57 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/25 12:15:29 by mvignes          ###   ########.fr       */
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

/// @brief create node var empty for export
/// @param cmd 
t_env	*create_node_var_empty(t_command *cmd)
{
	t_env	*new;
	char	**tab;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup(cmd->av[1]);
	if (!tab)
		return (free_tab(tab), NULL);
	tab[1] = ft_strdup("");
	if (!tab)
		return (free_tab(tab), NULL);
	tab[2] = NULL;
	new = ft_envnew(tab);
	if (!new)
		free_tab(tab);
	return (new);
}

/// @brief edit var in list t_env
/// @param cmd 
void	edit_var(t_command *cmd, t_env *node)
{
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
}

/// @brief create or edit the var in list t_env
/// @param cmd 
void	create_or_edit_var(t_command *cmd)
{
	t_env	*node;

	node = NULL;
	if (strchr(cmd->av[1], '='))
	{
		edit_var(cmd, node);
		if (node)
			return ;
	}
	else
	{
		node = create_node_var_empty(cmd);
		if (!node)
			return ;
		ft_envadd_back(&cmd->shell->env, node);
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
