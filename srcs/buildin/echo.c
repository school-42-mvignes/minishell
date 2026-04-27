/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:23:49 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/27 18:13:04 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief check if it’s a flag
/// @param av 
/// @return true == it’s a flag
static bool	check_flags(char *av)
{
	int	i;

	i = 0;
	if (av[i] == '-')
		i++;
	else
		return (false);
	while (av[i] == 'n')
		i++;
	if (av[i] == '\0')
		return (true);
	return (false);
}

/// @brief writes the requested text
/// @param cmd 
void	buildin_echo(t_command *cmd)
{
	int		i;
	bool	new_line;
	bool	first_word;

	new_line = false;
	first_word = true;
	i = 1;
	while (cmd->av[i])
	{
		while (check_flags(cmd->av[i]) && first_word == true)
		{
			i++;
			new_line = true;
		}
		if (!first_word)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmd->av[i++], 1);
		first_word = false;
	}
	if (!new_line)
		ft_putchar_fd('\n', 1);
	return ;
}
