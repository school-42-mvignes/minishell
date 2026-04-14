/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:14:18 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/14 13:06:56 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"



typedef struct s_command	t_command;


void			exec_node(t_node *node);
int				exec_pipe(t_node *node);
int				exec_or(t_node *node);
int				exec_and(t_node *node);

t_redir			*search_last_fd_redir(t_redir *redir); // voir si on sup
void			redirect_fd(int old_fd, int new_fd);
void			create_and_redir_file(t_redir *redir);
pid_t			create_fork(void);
int				create_pipe(int pipefd[2]);

int				what_the_outfile(t_redir *redir);

char			*find_path(char *cmd, char **envp);
char			*build_my_path(char *path, char *cmd);
char			*search_my_path(char **envp);
void			exec_cmd(t_node *node, char **args, char **envp);
void			exec_node_cmd(t_node *node);

#endif