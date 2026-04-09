/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:20:10 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/09 11:28:40 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell

#include "../includes/minishell.h"
// < Makefile ls -l | wc -l > outfile

// void print_tree(t_node *node)
// {
// 	int i;

// 	i = 0;
// 	if (!node)
// 		return ;
// 	if (node->type == NODE_CMD)
// 	{
// 		while (node->cmd->av[i])
// 		{
// 			printf("type = %d\n", node->type);
// 			printf("av[%d] = %s\n", i, node->cmd->av[i]);
// 			// printf("file = %s\n", node->cmd->redir->file);
// 			// printf("file = %i\n", node->cmd->redir->file_fd);
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		print_tree(node->left);
// 		print_tree(node->right);
// 		printf("type = %d\n", node->type);
// 	}
// }

// t_shell	*ft_shellnew(void)
// {
// 	t_shell	*element;
// 	int		status;

// 	status = 0;
// 	element = malloc(sizeof(t_shell));
// 	if (!element)
// 		return (NULL);
// 	element->env = NULL;
// 	element->exit_status = &status;
// 	return (element);
// }

static void	init_minishell(t_shell *shell, char **env)
{
	t_env	*lst_env;

	lst_env = call_env(env);
	// shell = ft_shellnew();
	shell->env = lst_env;
}

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

int	main(int ac, char **av, char **env)
{
	char	*buf;
	t_token	*cur;
	t_token	token;
	t_node *node;
	t_shell	shell;

	(void)ac;
	(void)av;
	cur = NULL;
	node = NULL;
	ft_memset(&shell, 0, (sizeof(t_shell)));
	init_minishell(&shell, env);
	while (1)
	{
		buf = readline("Minishell>");
		if (buf == NULL)
		{
			write(2, "exit\n", 5);
			exit_free_all(cur, node, &shell, buf);
		}
		add_history(buf);
		cur = lexer(buf, &token);
		if (cur == NULL)
			continue ;
		node = parse_and_or(&cur, &shell);
		if (node)
		{
			what_the_separator(node, &shell);
			if (what_the_buildin(node)) // fait l'init dans la creation de cmd
			 	exit_free_all(cur, node, &shell, buf);
			 else
			 	exec_cmd(node, node->cmd->av, rebuild_env(&node->cmd->shell->env));
		}
		// what_the_separator(node, &shell);
	}
}
