/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:20:10 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/20 16:57:21 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell
// (cd .. && lwqd || ls > test1.1) && ls | grep mi | wc > test1.2 && (cat < ../Makefile | grep printf > test1.3)

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
	ft_envclear(&node->cmd->shell->env, free);
	free(node->cmd->shell);
	free_token_lst(lst);
	free_node(node);
	// free shell
	rl_clear_history();
	
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
	shell = ft_shellnew(env);
	// init_minishell(&shell, env);
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
		if (cur == NULL)
			continue ;
		expand(cur, shell);
		node = parse_and_or(&cur, shell);
		avenger_assemble(node, shell);
		if (node)
		{
			shell->exit_status = exec_node(node);
			// free_node(node); // creer plein de probleme dans valgrind. trop de perte de temps si j'essaie de regler le probleme, voir avec max
		}
	}
}
