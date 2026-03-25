/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:51:04 by mmusquer          #+#    #+#             */
/*   Updated: 2026/03/25 20:33:52 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse_and_or(t_token **token)
{
	t_node	*node;
	t_node	*left;

	left = parse_pipe(token);
	while (*token && (((*token)->type == SP_AND) || ((*token)->type == SP_OR)))
	{
		node = malloc(sizeof(t_node));
		if (!node)
			return (NULL);
		memset(node, 0, sizeof(t_node));
		node->left = left;
		if ((*token)->type == SP_AND)
			node->type = NODE_AND;
		else
			node->type = NODE_OR;
		use_token(token);
		node->cmd = NULL;
		node->right = parse_pipe(token);
		left = node;
	}
	return (left);
}

t_node	*parse_pipe(t_token **token)
{
	t_node	*node;
	t_node	*left;

	left = parse_cmd(token);
	while (*token && ((*token)->type == SP_PIPE))
	{
		node = malloc(sizeof(t_node));
		if (!node)
			return (NULL);
		memset(node, 0, sizeof(t_node));
		node->left = left;
		node->type = NODE_PIPE;
		use_token(token);
		node->cmd = NULL;
		node->right = parse_cmd(token);
		left = node;
	}
	return (left);
}

t_redir	*parse_redir(t_token **token, t_command *cmd)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	memset(redir, 0, sizeof(t_redir));
	cmd->redir = redir; 
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

t_node	*parse_cmd(t_token **token)
{
	t_node		*node;
	t_token		*tmp;
	t_command	*cmd;
	int			count;
	int			i;

	tmp = *token;
	count = 0;
	i = 0;
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	memset(node, 0, sizeof(t_node));
	node->type = NODE_CMD;
	if (tmp->type == L_BRACKET)
	{
		use_token(token);
		node = parse_and_or(token);
		use_token(token);
		return (node);
	}
	while (tmp && ((tmp->type == WORD) || (tmp->type == S_QUOTE)
		|| (tmp->type == D_QUOTE)) || (tmp->type == REDIR_APP)
		|| (tmp->type == REDIR_HERE) || (tmp->type == REDIR_IN)
		|| (tmp->type == REDIR_OUT))
	{
		if ((tmp->type == REDIR_APP)
			|| (tmp->type == REDIR_HERE) || (tmp->type == REDIR_IN)
			|| (tmp->type == REDIR_OUT))
		{
			tmp = tmp->next;
			tmp = tmp->next;
		}
		else
		{
			count++;
			tmp = tmp->next;
		}
	}
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->av = malloc(sizeof(char *) * (count + 1));
	if (!cmd->av)
		return (NULL);
	while (*token && (((*token)->type == WORD) || ((*token)->type == D_QUOTE)
			|| ((*token)->type == S_QUOTE) || ((*token)->type == REDIR_APP)
			|| ((*token)->type == REDIR_HERE) || ((*token)->type == REDIR_IN)
			|| ((*token)->type == REDIR_OUT)))
	{
		if (((*token)->type == REDIR_APP) || ((*token)->type == REDIR_HERE)
			|| ((*token)->type == REDIR_IN) || ((*token)->type == REDIR_OUT))
			parse_redir(token, cmd);
		else
		{
			cmd->av[i] = (*token)->value;
			use_token(token);
			i++;
		}
	}
	node->cmd = cmd;
	return (node);
}


faire fonction addlast pour redir.