/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:20:34 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/23 13:45:38 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*lastlst(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*create_token(t_type token, char *value, int n)
{
	t_token	*new;
	char	*tmp;
	int		i;

	i = 0;
	if (!n)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	tmp = malloc(sizeof(char *) * (n + 1));
	if (!tmp)
		return (free(new), NULL);
	tmp[n] = '\0';
	new->type = token;
	while (i < n)
	{
		tmp[i] = value[i];
		i++;
	}
	new->value = tmp;
	new->next = NULL;
	return (new);
}

t_token	*add_token(t_token **lst, t_token *new_nod, int *status)
{
	t_token	*last;

	if (!lst || !new_nod)
		return (NULL);
	if (!*lst)
	{
		*lst = new_nod;
		return (NULL);
	}
	last = lastlst(*lst);
	last->next = new_nod;
	*status = 0;
	return (*lst);
}

void	free_token_lst(t_token *lst)
{
	t_token	*next;

	if (!lst)
		return ;
	while (lst)
	{
		next = lst->next;
		free(lst->value);
		free(lst);
		lst = next;
	}
	free(lst);
}
