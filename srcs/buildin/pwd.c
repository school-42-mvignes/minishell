/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:01 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/27 17:56:48 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief write path or the message error
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
