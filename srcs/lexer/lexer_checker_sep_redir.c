/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker_sep_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:17:52 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/07 11:24:43 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_sep(t_token *token)
{
	while (token->type == SPACE && token->next)
		token = token->next;
	if (token->type == SP_AND || token->type == SP_OR || token->type == SP_PIPE)
		return (1);
	return (0);
}

int	last_sep(t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	while (token->type != NONE)
	{
		if (is_sep(token))
			tmp = token;
		token = token->next;
	}
	if (tmp == NULL)
		return (0);
	if (next_token(tmp)->type == NONE)
		return (1);
	return (0);
}

int	double_sep(t_token *token)
{
	t_token	*next;

	while (token->next)
	{
		if (token->type == SPACE)
		{
			token = token->next;
			continue ;
		}
		next = next_token(token);
		if (is_sep(token) && is_sep(next))
			return (1);
		token = token->next;
	}
	return (0);
}

int	redir_file(t_token *token)
{
	t_token *next;

	while (token->next)
	{
		while (!is_redir(token))
			token = token->next;
		next = next_token(token);
		if (next->type != WORD && next->type != S_QUOTE
			&& next->type != D_QUOTE)
			return (1);
		token = token->next;
	}
	return (0);
}