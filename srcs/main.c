/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:20:10 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/24 16:22:08 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell
// funcheck ./minishell -c "ls | ls"
// valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell
#include "../includes/minishell.h"

static	int is_void(char *buf)
{
	int i;

	i = 0;
	while (buf[i] == ' ')
		i++;
	return (buf[i] == '\0');
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
	int status;

	status = shell->exit_status;
	ft_envclear(&shell->env, free);
	free(shell);
	if (lst)
		free_token_lst(lst);
	if (node)
		free_node(node);
	rl_clear_history();
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
	t_node *node;
	t_shell	*shell;

	(void)ac;
	(void)av;
	init_signal();
	shell = ft_shellnew(env, &token);
	if (!shell)
		return (1);
	while (1)
	{
		cur = NULL;
		node = NULL;
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
		if (is_void(buf))
		{
			free(buf);
			continue ;
		}
		add_history(buf);
		cur = lexer(buf, &token);
		if (!cur)
			shell->exit_status = 1;
		shell->free_the_token = cur;
		if (cur == NULL)
		{
			free(buf);
			continue ;
		}
		expand(cur, shell);
		node = parse_and_or(&cur, shell);
		shell->free_the_node = node;
		shell->exit_status = avenger_assemble(node, shell);
		if (shell->exit_status == 0 && node)
			shell->exit_status = exec_node(node);
		if (shell->exit_status == 130)
		{
			free(node);
			free_token_lst(cur);
			free(buf);
			rl_replace_line("", 0);
			rl_on_new_line();
			continue ;
		}
		free_node(node);
		// free_token_lst(&token);
		free_token_lst(cur);
		free(buf);
		cur = NULL;
		node = NULL;
	}
}
