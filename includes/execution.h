/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:14:18 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 17:16:09 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"



typedef struct s_command	t_command;

char			*find_path(char *cmd, char **envp);
char			*build_my_path(char *path, char *cmd);
char			*search_my_path(char **envp);
void			exec_cmd(t_command *pipex, char **args, char **envp);

#endif