/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:01 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/16 21:30:46 by mvignes          ###   ########.fr       */
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
	ft_putendl_fd(path, 1);
}
