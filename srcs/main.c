/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:20:10 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/26 17:04:10 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

static void	init_minishell(t_command *cmd, char **env)
{
	t_env	*lst_env;

	lst_env = call_env(env);
	cmd->shell = ft_shellnew();
	cmd->shell->env = lst_env;
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
	char		*line;
	t_command	cmd;

	(void)ac;
	(void)av;
	(void)env;
	ft_memset(&cmd, 0, (sizeof(t_command)));
	init_minishell(&cmd, env);
	while (1)
	{
		// ft_memset(&cmd, 0, (sizeof(t_command))); // clear all sauf l'env et peut etre la sortie {$?}
		// printf("testest");
		line = readline("Mini-shell>");
		parsing(&cmd, line);
	}
}
