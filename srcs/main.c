/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:20:10 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/14 14:21:55 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

#include "../includes/minishell.h"

t_shell	*ft_shellnew(char **env)
{
	t_shell	*element;
	int		status;

	status = 0;
	element = malloc(sizeof(t_shell));
	if (!element)
		return (NULL);
	element->env = call_env(env);
	element->exit_status = status;
	return (element);
}

/* static void	init_minishell(t_shell *shell, char **env)
{
	t_shell	shell;
} */

static void	exit_free_all(t_token *lst, t_node *node, t_shell *shell, char *buf)
{
	int status;

	status = shell->exit_status;
	free_token_lst(lst);
	free_node(node);
	// free shell
	rl_clear_history();
	// ft_envclear(node->cmd->shell->env, free);
	
	free(buf);
	exit(status);
	
}

/* static int do_node(t_node *node)
{
	int res;

	res = exec_the_buildin(node);
	if (res == 1)
		return (1);
	if (res == -1)
		exec_cmd(node, node->cmd->av, rebuild_env(&node->cmd->shell->env));
	return (0);
} */

int	main(int ac, char **av, char **env)
{
	char	*buf;
	t_token	*cur;
	t_token	token;
	t_node *node;
	t_shell	*shell;

	(void)ac;
	(void)av;
	cur = NULL;
	node = NULL;
	shell = ft_shellnew(env);
	// init_minishell(&shell, env);
	while (1)
	{
		buf = readline("Minishell>");
		if (buf == NULL)
		{
			write(2, "exit\n", 5);
			exit_free_all(cur, node, shell, buf);
		}
		add_history(buf);
		cur = lexer(buf, &token);
		if (cur == NULL)
			continue ;
		expand(cur, shell);
		node = parse_and_or(&cur, shell);
		if (node)
			exec_node(node);
		// printf("exit_status = %i\n", node->cmd->shell->exit_status);
		// if (node && node->type == NODE_CMD)
		// {
		// 	if (do_node(node))
		// 		exit_free_all(cur, node, shell, buf);
		// }
	}
}
