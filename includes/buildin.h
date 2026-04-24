/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:09:56 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/24 16:13:59 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

# include "minishell.h"

/* # ifndef SECURISATION
# define ROT 0
#endif */

/* # ifndef BUILDIN
#define ECHO ft_rot_x("echo", ROT)		// 1
#define CD ft_rot_x("cd", ROT)			// 2
#define PWD ft_rot_x("pwd", ROT)			// 3
#define ENV ft_rot_x("env", ROT)			// 4
#define EXPORT ft_rot_x("export", ROT)	// 5
#define UNSET ft_rot_x("unset", ROT)		// 6
#define EXIT ft_rot_x("exit", ROT)		// 7
#endif */

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

t_env				*search_key_var(t_env *env, char *key);
int					exec_the_buildin(t_node *node);
bool				is_one_buildin(t_node *node);
bool				exec_without_fork(t_node *node);
void				exec_buildin_without_fork(t_node *node);
void				free_exit(t_command *cmd);

void				buildin_unset(t_command *cmd);
void				buildin_export(t_command *cmd);
void				buildin_pwd(t_command *cmd);
void				buildin_env(t_command *cmd);
void				buildin_cd(t_command *cmd);
void				buildin_cd_cut(t_command *cmd, t_env *home);
void				buildin_echo(t_command *cmd);
int					buildin_exit(t_command *cmd);

#endif