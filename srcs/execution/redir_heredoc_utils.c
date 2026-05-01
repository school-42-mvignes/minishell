/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:08:23 by mmusquer          #+#    #+#             */
/*   Updated: 2026/05/01 08:55:24 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	assemble_cut(t_redir *redir, t_shell *shell)
{
	int	ret;

	while (redir)
	{
		if (redir->type == REDIR_HERE)
		{
			ret = do_heredoc(redir->file, shell, redir->do_not_expand);
			if (g_status == SIGINT)
			{
				g_status = 0;
				return (130);
			}
			else if (ret == -1)
				return (1);
			redir->heredoc_fd = ret;
		}
		redir = redir->next;
	}
	return (0);
}

int	avenger_assemble(t_node *node, t_shell *shell)
{
	t_redir	*redir;
	int		ret;

	if (!node)
		return (0);
	if (node->type == NODE_CMD)
	{
		redir = node->cmd->redir;
		ret = assemble_cut(redir, shell);
		if (ret == 130)
			return (130);
		else if (ret == 1)
			return (1);
	}
	else
	{
		avenger_assemble(node->left, shell);
		avenger_assemble(node->right, shell);
	}
	return (0);
}

void	check_quote_heredoc(t_token *token)
{
	t_token	*tmp;
	t_token	*next;

	tmp = token;
	while (tmp->next)
	{
		if (tmp->type == REDIR_HERE)
		{
			tmp->do_not_expand = 0;
			next = next_token(tmp);
			if (next->type == S_QUOTE || next->type == D_QUOTE)
				tmp->do_not_expand = 1;
		}
		tmp = tmp->next;
	}
}
