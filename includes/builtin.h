/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:09:56 by mvignes           #+#    #+#             */
/*   Updated: 2026/05/01 11:11:55 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

# ifndef BUILTIN
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

int				exec_the_builtin(t_node *node, t_shell *shell);
void			exec_builtin_without_fork(t_node *node);
bool			exec_without_fork(t_node *node);
bool			is_one_builtin(t_node *node);

void			builtin_unset(t_command *cmd);
void			builtin_export(t_command *cmd);
void			builtin_pwd(t_command *cmd);
void			builtin_env(t_command *cmd);
void			builtin_cd(t_command *cmd);
void			builtin_cd_cut(t_command *cmd, t_env *home);
void			builtin_echo(t_command *cmd);
int				builtin_exit(t_command *cmd);

t_env			*search_key_var(t_env *env, char *key, bool least);
void			error_getcwd(t_shell *shell, char *str, bool pwd, bool first);
void			empty_var(char *av, t_env *node, t_env *env);
bool			good_key_var_name(char *av);
void			error_export(t_command *cmd, int i);
void			free_exit(t_command *cmd);
int				is_num(char *str);

#endif