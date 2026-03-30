/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:20:10 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/30 16:24:21 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_tree(t_node *node)
{
	int i;

	i = 0;
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		while (node->cmd->av[i])
		{
			printf("type = %d\n", node->type);
			printf("av[%d] = %s\n", i, node->cmd->av[i]);
			i++;
		}
	}
	else
	{
		print_tree(node->left);
		print_tree(node->right);
		printf("type = %d\n", node->type);
	}
}

t_shell	*ft_shellnew(void)
{
	t_shell	*element;

	element = malloc(sizeof(t_shell));
	if (!element)
		return (NULL);
	element->env = NULL;
	element->exit_status = NULL;
	return (element);
}

static void	init_minishell(t_shell *shell, char **env)
{
	t_env	*lst_env;

	lst_env = call_env(env);
	shell = ft_shellnew();
	shell->env = lst_env;
}
//c'est pas senser etre ici mais dans le parsing, main pour tester les buldins//////
void	parsing(t_command *cmd, char *line)
{
	char	**tab;
	int		i;

	tab = ft_split(line, ' ');
	i = 0;
	cmd = malloc(sizeof(t_command));
	while (tab[i])
	{
		cmd->av[i] = ft_strdup(tab[i]);
		i++;
	}
	what_the_buildin(cmd);
}

int	main(int ac, char **av, char **env)
{
	char	*buf;
	t_token	*cur;
	t_token	token;
	t_node *node;
	t_shell	shell;

	(void)ac;
	(void)av;
	(void)env;
	ft_memset(&shell, 0, (sizeof(t_shell)));
	init_minishell(&shell, env);
	while (1)
	{
		// ft_memset(&cmd, 0, (sizeof(t_command))); // clear all sauf l'env et peut etre la sortie {$?}
		// printf("testest");
		buf = readline("Minishell>");
		cur = lexer(buf, &token);
		if (cur == NULL)
			continue ;
		node = parse_and_or(&cur);
		print_tree(node);
		// while (node->cmd->redir)
		// {
		// 	printf("redir file = %s\n redir type = %d\n", node->cmd->redir->file, node->cmd->redir->type);
		// 	node->cmd->redir = node->cmd->redir->next;
		// }
		free_token_lst(cur);
	}
}
