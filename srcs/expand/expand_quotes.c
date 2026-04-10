/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:53:11 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/10 16:06:02 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void cut_quotes(t_token *token)
{
	char *new_str;
	
	while (token->next)
	{
		if (token->type != D_QUOTE && token->type != S_QUOTE)
			token = token->next;
		else
		{
			new_str = ft_substr(token->value, 1, (ft_strlen(token->value) - 2));
			free(token->value);
			token->type = WORD;
			token->value = new_str;
			token = token->next;
		}
	}
}
