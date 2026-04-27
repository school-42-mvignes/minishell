/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 13:20:30 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/27 18:13:57 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_void(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] == ' ')
		i++;
	return (buf[i] == '\0');
}

int	verif_rl(t_token *cur, t_node *node, t_shell *shell, char *buf)
{
	if (buf == NULL)
	{
		write(2, "exit\n", 5);
		exit_free_all(cur, node, shell, buf);
	}
	if (g_status == SIGINT)
	{
		shell->exit_status = 130;
		g_status = 0;
	}
	if (is_void(buf))
	{
		free(buf);
		return (1);
	}
	return (0);
}

int	do_lexer(t_token **cur, t_token *token, t_shell *shell, char *buf)
{
	add_history(buf);
	*cur = lexer(buf, token);
	if (!*cur)
		shell->exit_status = 1;
	shell->free_the_token = *cur;
	if (*cur == NULL)
	{
		free(buf);
		return (1);
	}
	return (0);
}

int	do_parser_exec(t_token **cur, t_node **node, t_shell *shell, char *buf)
{
	*node = parse_and_or(cur, shell);
	shell->free_the_node = *node;
	shell->exit_status = avenger_assemble(*node, shell);
	if (shell->exit_status == 0 && *node)
		shell->exit_status = exec_node(*node);
	if (shell->exit_status == 130)
	{
		free_node(*node);
		free_token_lst(shell->free_the_token);
		free(buf);
		*cur = NULL;
		*node = NULL;
		shell->free_the_node = NULL;
		shell->free_the_token = NULL;
		rl_replace_line("", 0);
		rl_on_new_line();
		return (1);
	}
	return (0);
}

void	end_while(t_node **node, t_token **cur, t_shell *shell, char *buf)
{
	free_node(*node);
	free(buf);
	free_token_lst(shell->free_the_token);
	shell->free_the_token = NULL;
	*cur = NULL;
	*node = NULL;
}
