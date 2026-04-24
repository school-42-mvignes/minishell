/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:40:53 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/24 18:05:23 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_word(t_token *token)
{
	int	i;

	i = 0;
	while (token && ((token->type == WORD) || (token->type == S_QUOTE)
			|| (token->type == D_QUOTE) || (token->type == REDIR_APP)
			|| (token->type == REDIR_HERE) || (token->type == REDIR_IN)
			|| (token->type == REDIR_OUT) || (token->type == SPACES)))
	{
		if (token->type == SPACES)
			token = token->next;
		else if ((token->type == REDIR_APP) || (token->type == REDIR_HERE)
			|| (token->type == REDIR_IN) || (token->type == REDIR_OUT))
		{
			token = token->next;
			while (token->type == SPACES)
				token = token->next;
			token = token->next;
		}
		else
		{
			i++;
			token = token->next;
		}
	}
	return (i);
}

void	while_redir(t_token **token, t_command *cmd)
{
	int	i;

	i = 0;
	while (*token && (is_word_quote_redir(*token)
			|| ((*token)->type == SPACES)))
	{
		skip_spaces(token);
		if (!is_word_quote_redir(*token))
			break ;
		if (((*token)->type == REDIR_APP) || ((*token)->type == REDIR_HERE)
			|| ((*token)->type == REDIR_IN) || ((*token)->type == REDIR_OUT))
			add_redir(&cmd->redir, parse_redir(token));
		else
		{
			cmd->av[i] = ft_strdup((*token)->value);
			i++;
			use_token(token);
		}
	}
	cmd->av[i] = NULL;
}
