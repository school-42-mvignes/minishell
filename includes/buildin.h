/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:09:56 by mvignes           #+#    #+#             */
/*   Updated: 2026/05/01 09:43:27 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

# include "minishell.h"

# ifndef BUILDIN
#  define ECHOS "echo"
#  define CD "cd"
#  define PWD "pwd"
#  define ENV "env"
#  define EXPORT "export"
#  define UNSET "unset"
#  define EXIT "exit"
# endif

typedef struct s_command	t_command;
typedef struct s_node		t_node;
typedef struct s_env		t_env;
typedef struct s_shell		t_shell;

int				exec_the_buildin(t_node *node, t_shell *shell);
void			exec_buildin_without_fork(t_node *node);

void			buildin_unset(t_command *cmd);
void			buildin_export(t_command *cmd);
void			buildin_pwd(t_command *cmd);
void			buildin_env(t_command *cmd);
void			buildin_cd(t_command *cmd);
void			buildin_cd_cut(t_command *cmd, t_env *home);
void			buildin_echo(t_command *cmd);
int				buildin_exit(t_command *cmd);

void			error_getcwd(t_shell *shell, char *str, bool pwd, bool first);
void			empty_var(char *av, t_env *node, t_env *env);
bool			exec_without_fork(t_node *node);
bool			is_one_buildin(t_node *node);
t_env			*search_key_var(t_env *env, char *key, bool least);
void			free_exit(t_command *cmd);
int				is_num(char *str);
bool			dont_dash_in_key_var(char	*str);

#endif