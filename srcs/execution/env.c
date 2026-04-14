/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:46:23 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/14 13:04:37 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_lst_env(t_list *lst, t_env **env)
{
	char	**tab;
	t_env	*new;

	while (lst)
	{
		tab = split_in_two(lst->content, '=');
		if (!tab)
			return ;
		new = ft_envnew(tab);
		ft_envadd_back(env, new);
		lst = lst->next;
		free(tab);
	}
}

char	**rebuild_env(t_env **env)
{
	t_env	*tmp;
	char	*str_tmp;
	char	**tab;
	int		i;

	tmp = (*env);
	tab = malloc(sizeof(char *) * (ft_envsize(tmp) + 1));
	i = 0;
	while (tmp)
	{
		str_tmp = ft_strjoin(tmp->key_var, "=");
		tab[i] = ft_strjoin_gnl(str_tmp, tmp->var);
		if (!tab[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	error_message(char *message)
{
	ft_putendl_fd(message, 2);
	exit (1);
}

// A voir comment le mettre en place void	call_env(t_env *lst_env, char **env)

// void	call_env(t_env **lst_env, char **env)
t_env	*call_env(char **env)
{
	t_list	*lst = NULL;
	t_env	*lst_env = NULL;
	// char	**tab_env;

	split_tab_to_list(env, &lst);
	if (lst == NULL)
		error_message("env : proubleme lst pour split");
	init_lst_env(lst, &lst_env);
	if (lst_env == NULL)
		error_message("env : proubleme lst_env");
	
	ft_lstclear(&lst, free);
	// printf_env(lst_env);
	// tab_env = rebuild_env(&lst_env);
	// if (!tab_env)
	// 	error_message("env : c'est la merde");
	// printf("=*=*=*=*=*=*=*=*=*==*=*=*=*=*=*=*=*=*=*=*=*=\n");
	// int	i = 0;
	// while (tab_env[i])
	// 	printf("\033[1m%s\n\033[0m", tab_env[i++]);
	// free_tab(tab_env);
	// ft_lstclear(&lst, free);
	// ft_envclear(&lst_env, free);
	return (lst_env);
}

/* int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	call_env(env);
	return (0);
} */

/* int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list  *lst = NULL;
	t_env	*lst_env = NULL;
	char	**tab_env;

	split_tab_to_list(env, &lst);

	if (lst == NULL)
	{
		printf("proubleme lst\n");
		return (1);
	}
	printf_list(lst);
	init_lst_env(lst, &lst_env);
	if (lst_env == NULL)
	{
		printf("proubleme lst_env\n");
		return (1);
	}

	printf("========================================================================================\nLE MUR DU NORD OU DE BERLIN OU DU MEXIQUE /// COMME TU VEUX FRERO\n========================================================================================\n");

	printf_env(lst_env);

	tab_env = rebuild_env(&lst_env);
	if (!tab_env)
	{
		printf("c'est la merde\n");
		exit (1);
	}
	int	i = 0;
	while (tab_env[i])
		printf("\033[1m%s\n\033[0m", tab_env[i++]);

	free_tab(tab_env);
	ft_lstclear(&lst, free);
	ft_envclear(&lst_env, free);
	return (0);
} */
