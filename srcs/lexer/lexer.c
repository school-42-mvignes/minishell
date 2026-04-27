/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:52:18 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/27 16:42:51 by mmusquer         ###   ########.fr       */
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
	else if (str[i] == '|' || (str[i] == '&') || str[i] == '>' || str[i] == '<'
		|| str[i] == '(' || str[i] == ')')
	{
		i = lexer_sep(token, str, i);
	}
	else
		i = lexer_word(token, str, i);
	return (i);
}

static int	do_none(t_token **t_lst, char *str, int i, int *status)
{
	t_token	*tmp;

	tmp = create_token(NONE, str + i, 1);
	if (!tmp)
	{
		free_token_lst(*t_lst);
		return (1);
	}
	add_token(t_lst, tmp, status);
	if (lexer_checker(*t_lst) == 1)
		return (1);
	return (0);
}

// static void print_token(t_token *t_lst)
// {
// 	int		node;
// 	t_token *tmp;

// 	tmp = t_lst;
// 	node = 1;
// 	while(tmp)
// 	{
// 		printf("node nb : %i\n", node);
// 		printf("value = %s\n", tmp->value);
// 		printf("type = %i\n", tmp->type);
// 		tmp = tmp->next;
// 		node++;
// 	}
// }

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
			return (free_token_lst(token), free_token_lst(t_lst), NULL);
		add_token(&t_lst, create_token(token->type, str + j, i - j), &status);
		if (status == 1)
			return (NULL);
	}
	if (do_none(&t_lst, str, i, &status) == 1)
		return (NULL);
	check_quote_heredoc(t_lst);
	return (t_lst);
}
