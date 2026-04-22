/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:26:50 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/21 16:16:27 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief count node in the list linkend t_env
/// @param env 
/// @return size list t_env
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

/// @brief clear the list linkend t_env
/// @param env 
/// @param del 
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

/// @brief create new node for the list linkend t_env
/// @param tab 
/// @return new node in t_env
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
	{
		free(tab[0]);
		return (NULL);
	}
	element->next = NULL;
	return (element);
}

/// @brief search the last node in the list linkend t_env
/// @param lst 
/// @return last node
t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/// @brief add the node in the last linkend list t_env
/// @param lst 
/// @param new 
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
