/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker_bracket.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:19:51 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/07 11:28:38 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_bracket_balance(t_token *token)
{
	int	i;

	i = 0;
	while (token->next)
	{
		if (token->type == L_BRACKET)
			i++;
		if (token->type == R_BRACKET)
			i--;
		token = token->next;
	}
	if (i != 0)
		return (1);
	else
		return (0);
}

int	is_multi_subshell(t_token *token)
{
	int	i;

	i = 0;
	while (token->next && i <= 1)
	{
		if (token->type == L_BRACKET)
			i++;
		if (token->type == R_BRACKET)
			i--;
		token = token->next;
	}
	if (i != 0)
		return (1);
	else
		return (0);
}

int	is_sep_in_subshell(t_token *token)
{
	int	res;

	while (token->next)
	{
		if (token->type == L_BRACKET)
		{
			res = 0;
			token = token->next;
			while (token->type != R_BRACKET && token->next)
			{
				if (token->type == SP_AND || token->type == SP_OR
					|| token->type == SP_PIPE)
					res = 1;
				token = token->next;
			}
			if (res == 0)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	is_subshell_empty(t_token *token)
{
	int	res;

	while (token->next)
	{
		if (token->type == L_BRACKET)
		{
			res = 0;
			token = token->next;
			while (token->type != R_BRACKET && token->next)
			{
				if (token->type != SPACE)
					res = 1;
				token = token->next;
			}
			if (res == 0)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	sep_w_subshell(t_token *token)
{
	t_token *prev;
	t_token *next;

	prev = NULL;
	while (token->next)
	{
		if (token->type != SPACE && token->type != L_BRACKET)
			prev = token;
		if (token->type == L_BRACKET)
		{
			if (prev != NULL && prev->type != SP_AND && prev->type != SP_OR
				&& prev->type != SP_PIPE)
				return (1);
			while (token->type != R_BRACKET && token->next)
				token = token->next;
			next = next_token(token);
			if (next->type != SP_AND && next->type != SP_OR
				&& next->type != SP_PIPE && next->type != NONE)
				return (1);
		}
		token = token->next;
	}
	return (0);
}
