/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:01 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/22 16:38:20 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief write path
/// @param cmd 
void	buildin_pwd(t_command *cmd)
{
	char	*path;

	(void)cmd;
	path = getcwd(NULL, 0);
	if (path)
		ft_putendl_fd(path, 1);
	else
	{
		ft_putstr_fd("error retrieving current directory: getcwd: cannot", 2);
		error_message(" access parent directories: No such file or directory");
	}
	free(path);
}
