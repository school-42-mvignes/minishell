/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:14:18 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/30 21:31:12 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"



typedef struct s_command	t_command;


int				what_the_outfile(t_redir *redir);
void			what_the_separator(t_node *node, t_shell *shell);
void			exec_first_cmd(t_node *node, t_command *cmd, int pipe[2]);
void			exec_sec_cmd(t_node *node, t_command *cmd, int pipe[2]);

char			*find_path(char *cmd, char **envp);
char			*build_my_path(char *path, char *cmd);
char			*search_my_path(char **envp);
void			exec_cmd(t_node *node, char **args, char **envp);

#endif