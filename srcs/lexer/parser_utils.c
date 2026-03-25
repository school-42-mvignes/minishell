/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:16:29 by mmusquer          #+#    #+#             */
/*   Updated: 2026/03/25 20:30:27 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *use_token(t_token **token)
{
	t_token *tmp;

	tmp = *token;
	*token = (*token)->next;
	return (tmp);
}

t_redir	*add_token(t_token **lst, t_token *new_nod)
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
	return (*lst);
}