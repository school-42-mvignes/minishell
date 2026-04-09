/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:52:18 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/08 14:34:23 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	lexer_spaces(t_token **t_lst, char *str, int *i, int *status)
{
	int	j;

	j = *i;
	if (str[*i] != ' ')
		return (0);
	while (str[*i] == ' ')
		(*i)++;
	add_token(t_lst, create_token(SPACES, str + j, 1), status);
	return (1);
}

static int	lexer_while(t_token *token, char *str, int i)
{
	if (str[i] == '\'' || str[i] == '\"')
	{
		i = lexer_quote(token, str, i);
		if (i == -1)
		{
			write(2, "Error syntax\n", 13);
			return (-1);
		}
	}
	else if (str[i] == '|' || str[i] == '&' || str[i] == '>' || str[i] == '<'
		|| str[i] == '(' || str[i] == ')')
	{
		i = lexer_sep(token, str, i);
	}
	else
		i = lexer_word(token, str, i);
	return (i);
}

t_token	*lexer(char *str, t_token *token)
{
	t_token	*t_lst;
	int		status;
	int		i;
	int		j;

	i = 0;
	status = 0;
	t_lst = NULL;
	while (str[i])
	{
		j = i;
		if (lexer_spaces(&t_lst, str, &i, &status))
			continue ;
		i = lexer_while(token, str, i);
		if (i == -1)
			return (NULL);
		add_token(&t_lst, create_token(token->type, str + j, i - j), &status);
		if (status == 1)
			return (NULL);
	}
	add_token(&t_lst, create_token(NONE, str + i, 1), &status);
	if (lexer_checker(t_lst) == 1)
		return (NULL);
	return (t_lst);
}
