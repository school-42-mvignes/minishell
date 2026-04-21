/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:24:01 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/21 16:06:21 by mmusquer         ###   ########.fr       */
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
	free(path);
}
