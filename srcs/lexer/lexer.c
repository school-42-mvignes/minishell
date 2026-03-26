/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:52:18 by mmusquer          #+#    #+#             */
/*   Updated: 2026/03/26 18:07:18 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	lexer_while(t_token *token, char *str, int i, int j)
{
	if (str[i] == '\'' || str[i] == '\"')
	{
		i = lexer_quote(token, str, i, j);
		if (i == -1)
		{
			write(2, "Error syntax\n", 13);
			return (-1);
		}
	}
	else if (str[i] == '|' || str[i] == '&' || str[i] == '>' || str[i] == '<'
		|| str[i] == '(' || str[i] == ')')
	{
		i = lexer_sep1(token, str, i);
	}
	else
		i = lexer_word(token, str, i);
	return (i);
}

t_token	*lexer(char *str, t_token *token)
{
	t_token	*t_lst;
	int		i;
	int		j;

	i = 0;
	t_lst = NULL;
	while (str[i])
	{
		j = i;
		if (str[i] == ' ')
		{
			i++;
			continue ;
		}
		i = lexer_while(token, str, i, j);
		if (i == -1)
			return (NULL);
		add_token(&t_lst, create_token(token->type, str + j, i - j));
	}
	if (str[i] == '\0')
	{
		token->type = NONE;
		add_token(&t_lst, create_token(token->type, str + i, 1));
	}
	return (t_lst);
}
