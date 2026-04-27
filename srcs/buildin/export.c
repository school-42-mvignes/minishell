/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:57 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/27 17:57:24 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief write error export
/// @param cmd 
static void	error_export(t_command *cmd)
{
	char	*msg;

	msg = ft_strjoin("Minishell: export:", "`");
	msg = ft_strjoin_gnl(msg, cmd->av[1]);
	msg = ft_strjoin_gnl(msg, "': not a valid identifier");
	ft_putendl_fd(msg, 2);
	free(msg);
	cmd->shell->exit_status = 1;
}

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
	return (new);
}

/// @brief edit var in list t_env
/// @param cmd 
static void	edit_var(char *av, t_env *node, t_shell *shell)
{
	char	**tab;
	
	tab = split_in_two(av, '=');
	if (!tab)
		return ;
	node = search_key_var(shell->env, tab[0]);
	if (!node)
	{
		node = ft_envnew(tab);
		ft_envadd_back(&shell->env, node);
		free(tab);
	}
}

/// @brief create or edit the var in list t_env
/// @param cmd 
static void	create_or_edit_var(char *av, t_shell *shell)
{
	t_env	*node;

	node = NULL;
	if (strchr(av, '='))
	{
		edit_var(av, node, shell);
		if (node)
			return ;
	}
	else
	{
		node = create_node_var_empty(av);
		if (!node)
			return ;
		ft_envadd_back(&shell->env, node);
	}
}

/// @brief check write env export or create / edit var or error
/// @param cmd 
void	buildin_export(t_command *cmd)
{
	int	i;

	if (!cmd->av[1])
	{
		print_export(cmd->shell->env);
	}
	else
	{
		i = 1;
		while(cmd->av[i])
		{
			if ((ft_isalpha(cmd->av[i][0]) || cmd->av[i][0] == '_')
			&& dont_dash_in_key_var(cmd->av[i]))
				create_or_edit_var(cmd->av[i], cmd->shell);
			else
				error_export(cmd);
			i++;
		}
	}
}
