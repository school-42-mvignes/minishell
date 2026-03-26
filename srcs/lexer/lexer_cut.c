/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:11:45 by mmusquer          #+#    #+#             */
/*   Updated: 2026/03/26 18:07:26 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer_quote(t_token *token, char *str, int i, int j)
{
	int	g;

	g = i + 1;
	if (str[i] == '\'' || str[i] == '\"')
	{
		while (str[g] && str[g] != str[i])
			g++;
		if (str[g] == '\0')
			return (-1);
	}
	if (str[i] == '\'')
		token->type = S_QUOTE;
	if (str[i] == '\"')
		token->type = D_QUOTE;
	i++;
	while (str[i] && str[i] != str[j])
		i++;
	i++;
	return (i);
}

int	lexer_sep1(t_token *token, char *str, int i)
{
	if (str[i] == '|' && str[i + 1] == '|')
	{
		token->type = SP_OR;
		return (i + 2);
	}
	if (str[i] == '&' && str[i + 1] == '&')
	{
		token->type = SP_AND;
		return (i + 2);
	}
	if (str[i] == '|' && str[i + 1] != '|')
	{
		token->type = SP_PIPE;
		return (i + 1);
	}
	if (str[i] == '<' && str[i + 1] == '<')
	{
		token->type = REDIR_HERE;
		return (i + 2);
	}
	return (lexer_sep2(token, str, i));
}

int	lexer_sep2(t_token *token, char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
	{
		token->type = REDIR_APP;
		return (i + 2);
	}
	if (str[i] == '<' && str[i + 1] != '<')
	{
		token->type = REDIR_IN;
		return (i + 1);
	}
	if (str[i] == '>' && str[i + 1] != '>')
	{
		token->type = REDIR_OUT;
		return (i + 1);
	}
	return (lexer_sep3(token, str, i));
}

int	lexer_sep3(t_token *token, char *str, int i)
{
	int	g;

	g = i + 1;
	if (str[i] == '(')
	{
		while (str[g] && str[g] != ')')
			g++;
		if (str[g] == '\0')
		{
			write(2, "Error syntax\n", 13);
			return (-1);
		}
	}
	if (str[i] == '(')
	{
		token->type = L_BRACKET;
		return (i + 1);
	}
	if (str[i] == ')')
	{
		token->type = R_BRACKET;
		return (i + 1);
	}
	return (i);
}

int	lexer_word(t_token *token, char *str, int i)
{
	token->type = WORD;
	while (str[i] && str[i] != '|' && str[i] != '&' && str[i] != '>'
		&& str[i] != '<' && str[i] != '(' && str[i] != ')' && str[i] != ' ')
		i++;
	return (i);
}
