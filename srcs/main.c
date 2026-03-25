/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:20:10 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 13:07:13 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_decision_action(char *line)
{
	int	i;

	i = 0;
	if (!ft_strncmp("neuilles", line, 7))
		write(1, "TEAM DES GROS NEUILLES\n", 22);
	else
		while (line[i])
			write(1, &line[i++], 1);
	write(1, "\n", 1);
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
	ft_memset(&cmd, 0, (sizeof(t_command)));
	while (1)
	{
		// ft_memset(&cmd, 0, (sizeof(t_command))); // clear all sauf l'env et peut etre la sortie {$?}
		printf("testest");
		init_minishell(&cmd, env);
		write(1, "mini-neuilles >", 16);
		line = get_next_line(0);
		parsing(&cmd, line);
	}
}
