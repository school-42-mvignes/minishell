/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:52:18 by mmusquer          #+#    #+#             */
/*   Updated: 2026/03/16 17:57:58 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*lastlst(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*create_token(t_type token, char *value)
{
	t_token	*new;
	int		n;

	n = ft_strlen(value);
	if (!n)
		return (NULL);
	new = malloc(sizeof(t_token) * n);
	if (!new)
		return (NULL);
	new->token = token;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **lst, t_token *new_nod)
{
	t_token	*last;

	if (!lst || !new_nod)
		return (NULL);
	if (!*lst)
	{
		*lst = new_nod;
		return ;
	}
	last = lastlst(*lst);
	last->next = new_nod;
}

void	lexer(char *str)
{
	int type;
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else if (str[i] == '|' || str[i] == '&' || str[i] == '>'
				|| str[i] == '<' || str[i] == '(' || str[i] == ')')
		{
			if (str[i] == '|' && str[i + 1] == '|')
			{
				type = SP_OR;
				i += 2;
			}
			if (str[i] == '&' && str[i + 1] == '&')
			{
				type = SP_AND;
				i += 2;
			}
			if (str[i] == '|' && str[i + 1] != '|')
			{
				type = SP_PIPE;
				i++;
			}
			if (str[i] == '<' && str[i + 1] == '<')
			{
				type = REDIR_HERE;
				i += 2;
			}
			if (str[i] == '>' && str[i + 1] == '>')
			{
				type = REDIR_APP;
				i += 2;
			}
			if (str[i] == '<' && str[i + 1] != '<')
			{
				type = REDIR_OUT;
				i++;
			}
			if (str[i] == '>' && str[i + 1] != '>')
			{
				type = REDIR_IN;
				i++;
			}
			if (str[i] == '(' && str[i + 1] == '>')
			{
				type = REDIR_APP;
				i += 2;
			}
		}
	}
}
