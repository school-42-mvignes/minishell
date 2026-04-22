/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:02:45 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/22 11:16:14 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
==========================================
		METTRE DANS LA LIBFT
==========================================
*/
// void	ft_lst_create_and_addback(t_list **lst, char *str) // rajouter dans la libft
// {
// 	char	*tmp;
// 	t_list	*new_node;

// 	tmp = ft_strdup(str);
// 	if (!tmp)
// 		return ;
// 	new_node = ft_lstnew(tmp);
// 	if (!new_node)
// 	{
// 		free(tmp);
// 		return ;
// 	}
// 	ft_lstadd_back(lst, new_node);
// }

/*
==========================================
		METTRE DANS LA LIBFT
==========================================
*/
// void	ft_lst_sort(t_list *lst) // rajouter dans la libft
// {
// 	t_list	*i;
// 	t_list	*j;
// 	int		n;
// 	char	*tmp;

// 	i = lst;
// 	while (i)
// 	{
// 		j = i->next;
// 		while (j)
// 		{
// 			if (ft_strlen(i->content) >= ft_strlen(j->content))
// 				n = ft_strlen(i->content);
// 			else
// 				n = ft_strlen(j->content);
// 			if (ft_strncmp(i->content, j->content, n) > 0)
// 			{
// 				tmp = i->content;
// 				i->content = j->content;
// 				j->content = tmp;
// 			}
// 			j = j->next;
// 		}
// 		i = i->next;
// 	}
// }
/*
====================================================================================
====================================================================================
*/

/// @brief read all file in the directory
/// @param av 
/// @return list files match with the parameter
static t_list	*get_wildcard_files(char *av)
{
	DIR				*directory;
	struct dirent	*file;
	int				i;
	t_list			*lst_files;

	lst_files = NULL;
	directory = opendir(".");
	if (!directory)
		return (NULL);
	i = -1;
	while (++i < 2)
		(file = readdir(directory));
	while ((file = readdir(directory)))
	{
		if (file->d_name[0] == '.' && av[0] != '.')
			continue ;
		if (match(av, file->d_name))
			ft_lst_create_and_addback(&lst_files, file->d_name);
	}
	closedir(directory);
	return (lst_files);
}

/// @brief check star in the string and create list match parameter
/// @param lst 
/// @param str 
static void	check_star(t_list **lst, char *str)
{
	t_list	*file;
	t_list	*tmp;

	file = get_wildcard_files(str);
	if (!file)
	{
		ft_lst_create_and_addback(lst, str);
		return ;
	}
	ft_lst_sort(file);
	tmp = file;
	while (tmp)
	{
		ft_lst_create_and_addback(lst, tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&file, free);
}

/// @brief create the final list before rebuild char ** for execute
/// @param lst 
/// @param str 
static void add_to_final_list(t_list **lst, char *str)
{
	if (is_wildcard(str))
		check_star(lst, str);
	else
		ft_lst_create_and_addback(lst, str);
}

/// @brief search the file match with the parameter
/// @param av 
/// @return char ** with they files match the parameter
char	**exec_wildcard(char **av)
{
	t_list	*lst;
	char	**new_av;
	int		i;

	if (!av)
		return (NULL);
	i = 0;
	lst = NULL;
	while (av[i])
		add_to_final_list(&lst, av[i++]);
	new_av = rebuild_av_for_wildcard(lst);
	ft_lstclear(&lst, free);
	free_tab(av); 
	return (new_av);
}
