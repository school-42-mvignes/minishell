/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:14:18 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/09 19:18:30 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"



typedef struct s_command	t_command;


int		exec_line(t_node *node);
bool	is_one_buildin(t_node *node);

t_redir			*search_last_fd_redir(t_redir *redir);
void			redirect_fd(int old_fd, int new_fd);
pid_t			create_fork(void);
int				create_pipe(int pipefd[2]);
int				open_file_read(char *infile);

int				what_the_outfile(t_redir *redir);
int				what_the_separator(t_node *node, int *pipe);
void			what_the_first_separator(t_node *node, int *pipe);


void			exec_sec_cmd(t_node *node, t_command *cmd, int pipe[2]);
void			exec_first_cmd(t_node *node, t_command *cmd, int pipe[2]);

char			*find_path(char *cmd, char **envp);
char			*build_my_path(char *path, char *cmd);
char			*search_my_path(char **envp);
void			exec_cmd(t_node *node, char **args, char **envp);
void			exec_simple_cmd(t_node *node, int *pipe);

#endif