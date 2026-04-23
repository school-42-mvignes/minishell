/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:20:10 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/23 13:46:01 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell
// funcheck ./minishell -c "ls | ls"

#include "../includes/minishell.h"

t_shell	*ft_shellnew(char **env, t_token *token)
{
	t_shell	*element;
	int		status;

	status = 0;
	element = malloc(sizeof(t_shell));
	if (!element)
		return (NULL);
	element->free_the_token = token;
	element->env = call_env(env);
	element->exit_status = status;
	return (element);
}

void	exit_free_all(t_token *lst, t_node *node, t_shell *shell, char *buf)
{
	int status;

	status = shell->exit_status;
	ft_envclear(&shell->env, free);
	free(shell);
	free_token_lst(lst);
	free_node(node);
	rl_clear_history();
	free(buf);
	exit(status);
	
}

/// @brief the 'hand' of the best project you have ever seen
/// @param ac 
/// @param av 
/// @param env 
/// @return exit_status
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
	init_signal();
	shell = ft_shellnew(env, &token);
	while (1)
	{
		buf = readline("Minishell$ ");
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
		add_history(buf);
		cur = lexer(buf, &token);
		if (!cur)
		{
			shell->exit_status = 1;
			free_token_lst(&token);
		}
		shell->free_the_token = cur;
		if (cur == NULL)
			continue ;
		expand(cur, shell);
		node = parse_and_or(&cur, shell);
		shell->free_the_node = node;
		avenger_assemble(node, shell);
		if (node)
			shell->exit_status = exec_node(node);
		free_node(node);
		// free_token_lst(&token);
		free_token_lst(cur);
		cur = NULL;
		node = NULL;
	}
	free(buf);
}
