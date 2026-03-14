/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttest.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:46:23 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/14 02:27:29 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// LA SAINTE COMMANDE DU SEIGNEUR : cc ttest.c ../libft/ft_lstnew.c ../libft/ft_lstadd_back.c ../libft/ft_lstlast.c ../libft/ft_memset.c ../libft/ft_strlen.c ../libft/ft_strchr.c ../libft/ft_strlcpy.c ../libft/ft_strdup.c ../libft/ft_free_tab.c ../libft/ft_lstclear.c ../libft/ft_lstdelone.c
// pour la suite surement des fonctions dans ../libft/get_next_line_utils.c ou les recoder


#include "../../includes/minishell.h"

void	printf_list(t_list *lst)
{
	// printf("222\n");
	t_list	*tmp;

	// printf("223\n");
	tmp = lst;
	// printf("224\n");
	while (tmp)
	{
		// printf("JE SUIS PASSER ICI\n");
		printf("\n node lst ===%s\n", (char *)tmp->content);
		// printf("230\n");
		tmp = tmp->next;
	}
}

void	printf_env(t_env *lst)
{
	// printf("222\n");
	t_env	*tmp;
	int		i;

	// printf("223\n");
	tmp = lst;
	i = 0;
	// printf("224\n");
	while (tmp)
	{
		// printf("JE SUIS PASSER ICI\n");
		// printf("\033[0;35m \033[1m\n NODE ENV; key = {%s}, var = {%s}\n\033[0m", (char *)tmp->key_var, tmp->var);
		printf("\033[0;35m\033[1m%s=%s\n\033[0m", tmp->key_var, tmp->var);
		// printf("230\n");
		tmp = tmp->next;
		i++;
	}
}

char	**split_in_two(char *str, char c)
{
	char	**tab;
	char	*var_delimiter;
	size_t  key_len;

	tab = malloc(sizeof(char *) * 3);
	if (!tab) return (NULL);
	var_delimiter = ft_strchr(str, c);
	if (!var_delimiter)
		return (NULL);
	var_delimiter = &var_delimiter[+1];
	key_len = var_delimiter - str;
	tab[0] = malloc(sizeof(char) * (key_len));
	if (tab[0])
		ft_strlcpy(tab[0], str, key_len);
	tab[1] = ft_strdup(var_delimiter);
	tab[2] = NULL;
	return (tab);
}

void	ft_envdelone(t_list *env, void (*del)(void *))
{
	del(env->content);
	free(env);
}

void	ft_envclear(t_env **env, void (*del)(void *))
{
	t_env	*tmp;

	while (*env)
	{
		tmp = (*env)->next;
		ft_envdelone(*env, del);
		*env = tmp;
	}
}

t_env	*ft_envnew(char **tab)
{
	// int		i = -1;
	t_env	*element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (0);
	printf("\033[0;32m\n\n\n\n\n\nYOUHOU CEST MOI JAI TROUVER TAB[0] = {%s} et tab[1] = {%s}\n \033[0m", tab[0], tab[1]); // mis en commentaire car leak
	// while (tab[0][++i])
	// 	element->key_var[i] = tab[0][i];
	// element->key_var[i] = '\0';
	// i = -1;
	// while (tab[1][++i])
	// 	element->var = tab[1][i];
	// element->var[i] = '\0';
	
	element->key_var = ft_strdup(tab[0]);
	element->var = ft_strdup(tab[1]);
	element->next = 0;
	printf("\033[0;31m\nNODE ENV avant retourn; key = %s, var = %s\n\033[0m", element->key_var, element->var); // ICI CA MARCHE
	return (element); // PUIS QUAND CA PASSE ICI JE VAIS ME FAIRE ENCULER
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


void	init_lst_env(t_list *lst, t_env **env)
{
	int		i;
	char	**tab;
	t_env	*tmp;
	t_env	*new;

	i = 0;
	tmp = (*env);
	while (lst)
	{
		printf("YOUHOU CEST ICI QUE CA SEGMENTATION FAULT\n");
		tab = split_in_two(lst->content, '=');
		printf("YOUHOU CEST MOI JAI TROUVER TAB[0] = {%s} et tab[1] = {%s}\n", tab[0], tab[1]); // mis en commentaire car leak
		new = ft_envnew(tab);
		printf("\033[0;33m\n NODE ENV; key = %s, var = %s\n\033[0m", tmp->key_var, tmp->var);
		ft_envadd_back(env, new);
		free_tab(tab);
		lst = lst->next; // a voir si ca va pas poser trop de proubleme
	}
}

void	split_tab_to_list(char **old_tab, t_list **lst)
{
	int		i;
	t_list	*new;

	i = 0;
	while (old_tab[i])
	{
		new = ft_lstnew(old_tab[i]);
		ft_lstadd_back(lst, new); 
		i++;
	}
}

/* char	**rebuild_env(t_env **env)
{
	t_env	*tmp;
	char	*str_tmp;
	char	**tab;
	int		i;

	tmp = (*env);
	i = 0;
	while (tmp)
	{
		str_tmp = ft_strjoin_gnl(tmp->key_var, "=");
		tab[i] = ft_strjoin_gnl(str_tmp, tmp->var);
		i++;
		tmp = tmp->next;
	}
	return (tab);
} */

int main(int ac, char **av, char **env)
{
	t_list  *lst = NULL;
	t_env	*lst_env = NULL;
	// char	**tab_env;

	split_tab_to_list(env, &lst);

	if (lst == NULL)
	{
		printf("proubleme lst\n");
		return (1);
	}

	// printf("100\n");
	// char *test = lst->content;
	// printf("test = %s\n\n\n", test);
	printf_list(lst);
	init_lst_env(lst, &lst_env);
	if (lst_env == NULL)
	{
		printf("proubleme lst_env\n");
		return (1);
	}

	printf("========================================================================================\nLE MUR DU NORD OU DE BERLIN OU DU MEXIQUE /// COMME TU VEUX FRERO\n========================================================================================\n");
	printf("100\n");
	printf_env(lst_env); // ET LA CA FONCTION MAIS WTF FAUT ALLER SE FAIRE ENCULER

	// tab_env = rebuild_env(&lst_env);			// a voir lundi, commence a fatiguer


	// ft_lstclear(&lst, free);					// fait crash, a voir
	// ft_envclear(&lst_env, free);				// fait surement crash car pareil que l'autre


	// int i = -1;
	// while (tab_env[++i])
	// 	printf("tab_env[i] = %s", tab_env[i]);
	// free_tab(tab_env);
	return (0);
}
