/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:20:10 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/19 12:04:13 by mvignes          ###   ########.fr       */
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



int	main(void)
{
	char	*line;

	while (1)
	{
		write(1, "mini-neuilles >", 16);
		line = get_next_line(0);
		if (!ft_strncmp("exit", line, 6))
			break;
		else
			ft_decision_action(line);
	}
}
