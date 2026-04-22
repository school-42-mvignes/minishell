/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:57:48 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/22 18:30:06 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int do_heredoc(char *lim, t_shell *shell, int flag)
{
	int fd[2];
	t_token tmp;
	char *line;

	(void)shell;
	(void)flag;
	pipe(fd);
	while (1 && g_status != SIGINT)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line && g_status == SIGINT)
			return(close(fd[0]), close(fd[1]), -1);
		line[ft_strlen(line) - 1] = '\0';
		if (!line || (ft_strncmp(line, lim, ft_strlen(lim)) == 0))
		{
			free(line);
			break ;
		}
		ft_memset(&tmp, 0, sizeof(t_token));
		tmp.next = NULL;
		tmp.value = line;
		tmp.type = WORD;
		if (flag == 0)
			search_dollards(&tmp, shell);
		write(fd[1], tmp.value, ft_strlen(tmp.value));
		free(tmp.value);
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	g_status = 0;
	return (fd[0]);
}

int	avenger_assemble(t_node *node, t_shell *shell)
{
	t_redir *redir;
	int		ret;

	if (!node)
		return (0);	
	if (node->type == NODE_CMD)
	{
		redir = node->cmd->redir;
		while (redir)
		{
			if (redir->type == REDIR_HERE)
			{
				signal(SIGINT, controller_for_heredoc);
				signal(SIGQUIT, SIG_IGN);
				ret = do_heredoc(redir->file, shell, redir->do_not_expand);
				if (ret == -1)
					return (1);
				redir->heredoc_fd = ret;
				signal(SIGINT, controller);
				signal(SIGQUIT, SIG_IGN);
			}
			redir = redir->next;
		}
	}
	else
	{
		avenger_assemble(node->left, shell);
		avenger_assemble(node->right, shell);
	}
	return (0);
}

void check_quote_heredoc(t_token *token)
{
	t_token *tmp;
	t_token *next;
	
	tmp = token;
	while (tmp->next)
	{
		if (tmp->type == REDIR_HERE)
		{
			next = next_token(tmp);
			if (next->type == S_QUOTE || next->type == D_QUOTE)
				tmp->do_not_expand = 1;
		}
		tmp = tmp->next;
	}
}
//  && (ft_strlen(line) - 1) == ft_strlen(lim)