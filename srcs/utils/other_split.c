/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:09:19 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/16 21:42:09 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief Function that is used to split in half from the first occurrence c
/// @param str 
/// @param c 
/// @return char **
char	**split_in_two(char *str, char c)
{
	char	**tab;
	char	*var_delimiter;
	int		key_len;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	var_delimiter = ft_strchr(str, c);
	if (!var_delimiter)
		return (NULL);
	var_delimiter = &var_delimiter[+1];
	key_len = ft_strlen(str) - ft_strlen(var_delimiter);
	tab[0] = ft_substr(str, 0, (key_len - 1));
	if (!tab[0])
		return (NULL);
	tab[1] = ft_strdup(var_delimiter);
	if (!tab[1])
		return (NULL);
	tab[2] = NULL;
	return (tab);
}

/// @brief Function that serves to split a whole **tab into a t_list
/// @param old_tab 
/// @param lst 
void	split_tab_to_list(char **old_tab, t_list **lst)
{
	int		i;
	t_list	*new;
	char	*envi;

	i = 0;
	while (old_tab[i])
	{
		envi = ft_strdup(old_tab[i]);
		new = ft_lstnew(envi);
		if (!new)
			break ;
		ft_lstadd_back(lst, new);
		i++;
	}
}
