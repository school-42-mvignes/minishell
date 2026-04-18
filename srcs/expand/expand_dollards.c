/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:41:51 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/18 13:50:14 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int create_new_value(t_token *token, int start, int i, char *value)
{
	char *before;
	char *after;
	char *new_str;
	int l;
	
	l = ft_strlen(token->value + i);
	before = ft_substr(token->value, 0, start);
	after = ft_substr(token->value, i, l);
	new_str = ft_strjoin(before, value);
	free(before);
	before = new_str;
	before = ft_strjoin(new_str, after);
	free(before);
	free(after);
	free(token->value);
	token->value = new_str;
	i = start + ft_strlen(value);
	return (i);
}

static void interrogation_mark(t_token *token, int j, int i, t_shell *shell)
{
	char *m;

	m = ft_itoa(shell->exit_status % 255);
	create_new_value(token, j - 1, i, m);
	free(m);
}

static void replace_dollards(t_token *token, int *i, t_shell *shell)
{
	int j;
	char *tmp;
	t_env *true_value;
	
	tmp = NULL;
	(*i)++;
	j = (*i);
	if (token->value[(*i)] == '?')
	{
		(*i)++;
		interrogation_mark(token, j, *i, shell);
		return ;
	}		
	while (ft_isalnum(token->value[*i]) || token->value[*i] == '_')
		(*i)++;
	tmp = ft_substr(token->value, j, *i - j + 1);
	true_value = search_key_var(shell->env, tmp);
	free(tmp);
	if (true_value)
		tmp = true_value->var;
	else
		tmp = "";
	*i = create_new_value(token, j - 1, *i, tmp);
}

void	search_dollards(t_token *token, t_shell *shell)
{
	int i;

	while (token)
	{
		i = 0;
		if (token->type != WORD && token->type != D_QUOTE)
		{
			token = token->next;
			continue ;
		}
		while (token->value[i])
		{
			if (token->value[i] == '$'
				&& token->value[i + 1] != ft_is_space(i + 1))
				replace_dollards(token, &i, shell);
			i++;
		}
		token = token->next;
	}
}
