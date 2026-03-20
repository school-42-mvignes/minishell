/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:14:38 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/19 23:46:25 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	printf_list(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("\n node lst ===  %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	printf_env(t_env *lst)
{
	t_env	*tmp;
	int		i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (tmp->var[0] == '\0')
			printf("\033[0;35m\033[1m%s=%s\n\033[0m", tmp->key_var, "");
		else
			printf("\033[0;35m\033[1m%s=%s\n\033[0m", tmp->key_var, tmp->var);
		tmp = tmp->next;
		i++;
	}
}
