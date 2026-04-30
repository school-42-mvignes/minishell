/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:14:38 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/30 09:37:43 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief writes the entire linked list "t_list"
/// @param lst 
void	print_list(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("\n node lst ===  %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

/// @brief writes the entire linked list "t_env"
/// @param lst 
void	print_env(t_env *lst)
{
	t_env	*tmp;
	char	*msg;

	tmp = lst;
	while (tmp)
	{
		if (tmp->egal_init)
		{
			msg = ft_strjoin(tmp->key_var, "=");
			if (tmp->var[0])
				msg = ft_strjoin_gnl(msg, tmp->var);
			ft_putendl_fd(msg, 1);
			free(msg);
		}
		tmp = tmp->next;
	}
}

/// @brief writes the entire linked list "t_env"  for thebuildin export
/// @param lst 
void	print_export(t_env *lst)
{
	t_env	*tmp;
	char	*msg;

	tmp = lst;
	while (tmp)
	{
		msg = ft_strjoin("export ", tmp->key_var);
		msg = ft_strjoin_gnl(msg, "=\"");
		if (tmp->var[0])
			msg = ft_strjoin_gnl(msg, tmp->var);
		msg = ft_strjoin_gnl(msg, "\"\n");
		ft_putstr_fd(msg, 1);
		free(msg);
		tmp = tmp->next;
	}
}
