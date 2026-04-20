/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:16:29 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/08 16:07:04 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_redir	*last_redir(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

t_token	*use_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	*token = (*token)->next;
	return (tmp);
}

t_redir	*add_redir(t_redir **redir, t_redir *new_redir)
{
	t_redir	*last;

	if (!redir || !new_redir)
		return (NULL);
	if (!*redir)
	{
		*redir = new_redir;
		return (NULL);
	}
	last = last_redir(*redir);
	last->next = new_redir;
	return (*redir);
}

void	skip_spaces(t_token **token)
{
	while ((*token)->type == SPACES)
		use_token(token);
}

int	is_word_quote_redir(t_token *token)
{
	if ((token->type == WORD) || (token->type == D_QUOTE)
		|| (token->type == S_QUOTE) || (token->type == REDIR_APP)
		|| (token->type == REDIR_HERE) || (token->type == REDIR_IN)
		|| (token->type == REDIR_OUT))
		return (1);
	return (0);
}
