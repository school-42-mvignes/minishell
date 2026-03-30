/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:26:50 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/20 01:04:28 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_envsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	ft_envclear(t_env **env, void (*del)(void *))
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		if ((*env)->key_var)
			del((*env)->key_var);
		if ((*env)->var)
			del((*env)->var);
		if ((*env))
			del((*env));
		*env = tmp;
	}
}

t_env	*ft_envnew(char **tab)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	element->key_var = tab[0];
	if (!element->key_var)
		return (NULL);
	element->var = tab[1];
	if (!element->var)
		return (NULL);
	element->next = NULL;
	return (element);
}

t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_envlast(*lst);
	last->next = new;
}
