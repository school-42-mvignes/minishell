/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:14:38 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/25 12:42:08 by mvignes          ###   ########.fr       */
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

	tmp = lst;
	while (tmp)
	{
		if (tmp->var[0] != '\0')
		{
			ft_putstr_fd(tmp->key_var, 1);
			ft_putchar_fd('=', 1);
			if (tmp->var[0])
				ft_putstr_fd(tmp->var, 1);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
}

/// @brief writes the entire linked list "t_env"  for thebuildin export
/// @param lst 
void	print_export(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(tmp->key_var, 1);
		ft_putchar_fd('=', 1);
		ft_putchar_fd('\"', 1);
		if (tmp->var[0])
			ft_putstr_fd(tmp->var, 1);
		ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}
