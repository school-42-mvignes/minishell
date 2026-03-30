/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:16:29 by mmusquer          #+#    #+#             */
/*   Updated: 2026/03/26 18:27:06 by mmusquer         ###   ########.fr       */
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

int	count_word(t_token *tmp)
{
	int	i;

	i = 0;
	while (tmp && ((tmp->type == WORD) || (tmp->type == S_QUOTE)
			|| (tmp->type == D_QUOTE) || (tmp->type == REDIR_APP)
			|| (tmp->type == REDIR_HERE) || (tmp->type == REDIR_IN)
			|| (tmp->type == REDIR_OUT)))
	{
		if ((tmp->type == REDIR_APP) || (tmp->type == REDIR_HERE)
			|| (tmp->type == REDIR_IN) || (tmp->type == REDIR_OUT))
		{
			tmp = tmp->next;
			tmp = tmp->next;
		}
		else
		{
			i++;
			tmp = tmp->next;
		}
	}
	return (i);
}

void	while_redir(t_token **token, t_command *cmd)
{
	int	i;

	i = 0;
	while (*token && (((*token)->type == WORD) || ((*token)->type == D_QUOTE)
			|| ((*token)->type == S_QUOTE) || ((*token)->type == REDIR_APP)
			|| ((*token)->type == REDIR_HERE) || ((*token)->type == REDIR_IN)
			|| ((*token)->type == REDIR_OUT)))
	{
		if (((*token)->type == REDIR_APP) || ((*token)->type == REDIR_HERE)
			|| ((*token)->type == REDIR_IN) || ((*token)->type == REDIR_OUT))
			add_redir(&cmd->redir, parse_redir(token));
		else
		{
			cmd->av[i] = (*token)->value;
			use_token(token);
			i++;
		}
	}
}
