/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:14:38 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/31 16:58:28 by mmusquer         ###   ########.fr       */
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

	tmp = lst;
	while (tmp)
	{
		if (tmp->var[0] == '\0')
			printf("\033[0;35m\033[1m%s=%s\n\033[0m", tmp->key_var, "");
		else
			printf("\033[0;35m\033[1m%s=%s\n\033[0m", tmp->key_var, tmp->var);
		tmp = tmp->next;
	}
}
