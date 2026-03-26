/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:40:34 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 20:19:10 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_and(t_command *cmd1, t_command *cmd2)
{
	
}
void	exec_or(t_command *cmd1, t_command *cmd2)
{
	
}

void	exec_pipe(t_command *cmd1, t_command *cmd2)
{
	
}

void	what_the_separator(t_command *cmd)
{
	if (cmd->sep == SP_AND)
		exec_and(cmd, cmd->next);
	else if (cmd->sep == SP_OR)
		exec_or(cmd, cmd->next);
	else if (cmd->sep == SP_PIPE)
		exec_pipe(cmd, cmd->next);
}
