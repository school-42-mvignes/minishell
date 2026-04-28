/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:17:16 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/28 14:04:43 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer_checker(t_token *token)
{
	int	res;

	res = 0;
	res = first_sep(token);
	res |= last_sep(token);
	res |= double_sep(token);
	res |= redir_file(token);
	res |= is_bracket_balance(token);
	res |= is_multi_subshell(token);
	if (res)
	{
		if (res == 1)
			write(2, "Error syntax\n", 13);
		free_token_lst(token);
		return (1);
	}
	return (0);
}

t_token	*next_token(t_token *token)
{
	token = token->next;
	while (token->type == SPACES && token->next)
		token = token->next;
	return (token);
}

int	is_sep(t_token *token)
{
	if (token->type == SP_AND || token->type == SP_OR
		|| token->type == SP_PIPE)
		return (1);
	return (0);
}

int	is_redir(t_token *token)
{
	if (token->type == REDIR_APP || token->type == REDIR_HERE
		|| token->type == REDIR_IN || token->type == REDIR_OUT)
		return (1);
	return (0);
}
