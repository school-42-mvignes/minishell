/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_concatenate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:06:17 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/10 16:26:56 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void concatenate(t_token *token)
{
	char *new_str;
	t_token *tmp;
	while (token->next)
	{
		if (token->type == WORD && token->next->type == WORD)
		{
			new_str = ft_strjoin(token->value, token->next->value);
			free(token->value);
			token->value = new_str;
			tmp = token->next;
			token->next = tmp->next;
			free(tmp->value);
			free(tmp);
			continue ;
		}
		else
			token = token->next;
	}
}