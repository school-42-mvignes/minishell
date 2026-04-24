/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:52:24 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/24 15:23:39 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief check if the redir is wildcard
/// @param str 
/// @return true == wildcard in the redir
bool	wildcard_redir(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

/// @brief check if there is a wildcard in the character string
/// @param str 
/// @return true == wildcard in the character string
bool	is_wildcard(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

/// @brief check if the character string matches the parameter
/// @param pat 
/// @param str 
/// @return true == match confirm on any file
bool	match(char *pat, char *str)
{
	if (!*pat && !*str)
		return (true);
	if (*pat == '*')
	{
		if (match(pat + 1, str))
			return (true);
		if (*str && match(pat, str + 1))
			return (true);
		return (false);
	}
	if (*pat == *str)
		return (match(pat + 1, str + 1));
	return (false);
}

/// @brief rebuild char ** for the file match with the parameter
/// @param lst 
/// @return char **
char	**rebuild_av_for_wildcard(t_list *lst)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (lst)
	{
		tab[i++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}
