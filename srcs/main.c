/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:20:10 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/28 15:04:30 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_minishell(int ac, char **av)
{
	(void)ac;
	(void)av;
	init_signal();
}

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

void	exit_free_all(t_token *lst, t_node *node, t_shell *shell, char *b)
{
	int	status;

	status = shell->exit_status;
	ft_envclear(&shell->env, free);
	free(shell);
	if (lst)
		free_token_lst(lst);
	if (node)
		free_node(node);
	rl_clear_history();
	if (b)
		free(b);
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
	t_node	*node;
	t_shell	*shell;

	(init_minishell(ac, av), shell = ft_shellnew(env, &token));
	if (!shell)
		return (1);
	while (1)
	{
		cur = NULL;
		node = NULL;
		shell->free_the_token = &token;
		buf = readline("Minishell$ ");
		if (verif_rl(cur, node, shell, buf))
			continue ;
		if (do_lexer(&cur, &token, shell, buf))
			continue ;
		expand(cur, shell);
		if (do_parser(&cur, &node, shell, buf))
			continue ;
		end_while(&node, &cur, shell, buf);
	}
}
