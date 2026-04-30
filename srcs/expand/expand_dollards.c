/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:41:51 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/30 14:36:33 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_new_value(t_token *token, int start, int i, char *value)
{
	char	*before;
	char	*after;
	char	*new_str;
	int		l;
	char	*tmp;

	l = ft_strlen(token->value + i);
	before = ft_substr(token->value, 0, start);
	after = ft_substr(token->value, i, l);
	new_str = ft_strjoin(before, value);
	free(before);
	before = new_str;
	tmp = ft_strjoin(new_str, after);
	free(new_str);
	free(after);
	free(token->value);
	token->value = tmp;
	i = start + ft_strlen(value) - 1;
	return (i);
}

static void	interrogation_mark(t_token *token, int j, int *i, t_shell *shell)
{
	char	*m;

	(*i)++;
	m = ft_itoa(shell->exit_status % 255);
	create_new_value(token, j - 1, *i, m);
	free(m);
}

static void	i_was_missing_two_line(char **tmp, int *i, int *j)
{
	*tmp = NULL;
	(*i)++;
	*j = (*i);
}

static void	replace_dollards(t_token *token, int *i, t_shell *shell)
{
	int		j;
	char	*tmp;
	t_env	*true_value;

	i_was_missing_two_line(&tmp, i, &j);
	if (token->value[(*i)] == '?')
	{
		interrogation_mark(token, j, i, shell);
		return ;
	}
	if (token->value[*i] == '\0' || token->value[*i] == '\''
		|| token->value[*i] == '\"' || token->value[*i] == ' ')
		return ;
	while (ft_isalnum(token->value[*i]) || token->value[*i] == '_')
		(*i)++;
	tmp = ft_substr(token->value, j, (*i - j));
	true_value = search_key_var(shell->env, tmp, false);
	free(tmp);
	if (true_value)
		tmp = true_value->var;
	else
		tmp = "";
	*i = create_new_value(token, j - 1, *i, tmp);
	if (token->value[0] == '\0')
		token->type = SPACES;
}

void	search_dollards(t_token *token, t_shell *shell)
{
	int	i;

	while (token)
	{
		i = 0;
		if (token->type != WORD && token->type != D_QUOTE)
		{
			token = token->next;
			continue ;
		}
		if (token->do_not_expand == 1)
		{
			token = token->next;
			continue ;
		}
		while (token->value[i])
		{
			if (token->value[i] == '$' && token->value[i + 1] != ft_is_space(i
					+ 1))
				replace_dollards(token, &i, shell);
			i++;
		}
		token = token->next;
	}
}
