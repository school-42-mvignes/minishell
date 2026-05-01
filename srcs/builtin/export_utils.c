/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 16:13:08 by mvignes           #+#    #+#             */
/*   Updated: 2026/05/01 11:11:45 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief write error export
/// @param cmd 
void	error_export(t_command *cmd, int i)
{
	char	*msg;

	msg = ft_strjoin("Minishell: export:", "`");
	msg = ft_strjoin_gnl(msg, cmd->av[i]);
	msg = ft_strjoin_gnl(msg, "': not a valid identifier");
	ft_putendl_fd(msg, 2);
	free(msg);
	cmd->shell->exit_status = 1;
}

/// @brief check is the good name for the key var
/// @param av 
/// @return true == good name, false == caractere not good
bool	good_key_var_name(char *av)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(av[i]) || av[i] == '_'))
		return (false);
	while ((ft_isalnum(av[i]) || av[i] == '_'))
		i++;
	if (av[i] == '=' || av[i] == '\0')
		return (true);
	if (av[i] == '+' && av[i + 1] == '=')
		return (true);
	return (false);
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
