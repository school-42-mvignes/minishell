/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:51:04 by mmusquer          #+#    #+#             */
/*   Updated: 2026/03/30 13:16:19 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*parse_and_or(t_token **token, t_shell *shell)
{
	t_node	*node;
	t_node	*left;

	left = parse_pipe(token, shell);
	while (*token && (((*token)->type == SP_AND) || ((*token)->type == SP_OR)))
	{
		node = malloc(sizeof(t_node));
		if (!node)
			return (NULL);
		ft_memset(node, 0, sizeof(t_node));
		node->left = left;
		if ((*token)->type == SP_AND)
			node->type = NODE_AND;
		else
			node->type = NODE_OR;
		use_token(token);
		node->cmd = NULL;
		node->right = parse_pipe(token, shell);
		left = node;
	}
	return (left);
}

t_node	*parse_pipe(t_token **token, t_shell *shell)
{
	t_node	*node;
	t_node	*left;

	left = parse_cmd(token, shell);
	while (*token && ((*token)->type == SP_PIPE))
	{
		node = malloc(sizeof(t_node));
		if (!node)
			return (NULL);
		ft_memset(node, 0, sizeof(t_node));
		node->left = left;
		node->type = NODE_PIPE;
		use_token(token);
		node->cmd = NULL;
		node->right = parse_cmd(token, shell);
		left = node;
	}
	return (left);
}

t_redir	*parse_redir(t_token **token)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	ft_memset(redir, 0, sizeof(t_redir));
	if (*token && (((*token)->type == REDIR_APP)
			|| ((*token)->type == REDIR_HERE) || ((*token)->type == REDIR_IN)
			|| ((*token)->type == REDIR_OUT)))
	{
		redir->type = (*token)->type;
		use_token(token);
		redir->file = (*token)->value;
		use_token(token);
	}
	return (redir);
}

t_node	*parse_bracket(t_token **token, t_node *node, t_token *tmp,
	t_shell *shell)
{
	if (tmp->type == L_BRACKET)
	{
		use_token(token);
		node = parse_and_or(token, shell);
		use_token(token);
		return (node);
	}
	return (node);
}

t_node	*parse_cmd(t_token **token, t_shell *shell)
{
	t_node		*node;
	t_token		*tmp;
	t_command	*cmd;

	tmp = *token;
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_node));
	node->type = NODE_CMD;
	parse_bracket(token, node, tmp, shell);
	if (tmp->type == L_BRACKET)
		return (node);
	node->count = count_word(tmp);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->av = malloc(sizeof(char *) * (node->count + 1));
	if (!cmd->av)
		return (NULL);
	while_redir(token, cmd);
	node->cmd = cmd;
	cmd->shell = shell;
	return (node);
}
