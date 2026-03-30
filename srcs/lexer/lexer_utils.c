/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:20:34 by mmusquer          #+#    #+#             */
/*   Updated: 2026/03/30 16:15:13 by mmusquer         ###   ########.fr       */
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
	tmp = malloc(n + 1);
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
	if ((last->type == SP_AND || last->type == SP_OR || last->type == SP_PIPE
			|| last->type == REDIR_APP || last->type == REDIR_HERE
			|| last->type == REDIR_IN || last->type == REDIR_OUT)
		&& (new_nod->type == SP_AND || new_nod->type == SP_OR
			|| new_nod->type == SP_PIPE || new_nod->type == REDIR_APP
			|| new_nod->type == REDIR_HERE || new_nod->type == REDIR_IN
			|| new_nod->type == REDIR_OUT))
	{
		write(2, "Error sytaxe\n", 13);
		*status = 1;
		return (NULL);
	}
	last->next = new_nod;
	status = 0;
	return (*lst);
}

void	free_token_lst(t_token *lst)
{
	t_token	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->value);
		free(lst);
		lst = next;
	}
}
