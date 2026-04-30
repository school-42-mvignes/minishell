/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:57 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/30 16:13:52 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief write error export
/// @param cmd 
static void	error_export(t_command *cmd, int i)
{
	char	*msg;

	msg = ft_strjoin("Minishell: export:", "`");
	msg = ft_strjoin_gnl(msg, cmd->av[i]);
	msg = ft_strjoin_gnl(msg, "': not a valid identifier");
	ft_putendl_fd(msg, 2);
	free(msg);
	cmd->shell->exit_status = 1;
}

/// @brief edit var in list t_env
/// @param cmd 
static void	edit_var(char *av, t_env *node, t_shell *shell)
{
	char	**tab;

	tab = split_in_two(av, '=');
	if (!tab)
		return ;
	node = search_key_var(shell->env, tab[0], false);
	if (!node)
	{
		node = ft_envnew(tab);
		node->egal_init = true;
		ft_envadd_back(&shell->env, node);
		free(tab);
	}
	else
	{
		free(node->var);
		node->egal_init = true;
		node->var = ft_strdup(tab[1]);
		free_tab(tab);
	}
}

/// @brief edit var in list t_env
/// @param cmd 
static void	edit_add_value_var(char *av, t_env *node, t_shell *shell)
{
	char	**tab;

	tab = split_in_two(av, '=');
	if (!tab)
		return ;
	node = search_key_var(shell->env, tab[0], true);
	if (!node)
	{
		node = ft_envnew(tab);
		node->egal_init = true;
		ft_envadd_back(&shell->env, node);
		free(tab);
	}
	else
	{
		node->var = ft_strjoin_gnl(node->var, tab[1]);
		node->egal_init = true;
		free_tab(tab);
	}
}

/// @brief create or edit the var in list t_env
/// @param cmd 
static void	create_or_edit_var(char *av, t_shell *shell)
{
	t_env	*node;
	char	*tmp;

	node = NULL;
	tmp = strchr(av, '+');
	if (strchr(av, '='))
	{
		if (ft_strlen(tmp) - 1 == ft_strlen(strchr(av, '=')))
			edit_add_value_var(av, node, shell);
		else
			edit_var(av, node, shell);
		if (node)
			return ;
	}
	else
		empty_var(av, node, shell->env);
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
		while (cmd->av[i])
		{
			if ((ft_isalpha(cmd->av[i][0]) || cmd->av[i][0] == '_')
			&& dont_dash_in_key_var(cmd->av[i]))
				create_or_edit_var(cmd->av[i], cmd->shell);
			else
				error_export(cmd, i);
			i++;
		}
	}
}
