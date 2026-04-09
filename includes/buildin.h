/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:09:56 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/09 11:37:39 by mvignes          ###   ########.fr       */
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
#  define ECHO "echo"     // 1
#  define CD "cd"         // 2
#  define PWD "pwd"       // 3
#  define ENV "env"       // 4
#  define EXPORT "export" // 5
#  define UNSET "unset"   // 6
#  define EXIT "exit"     // 7
# endif

typedef struct s_command	t_command;
typedef struct s_node		t_node;

t_env						*search_key_var(t_env *env, char *key);
int							what_the_buildin(t_node *node);

void						buildin_unset(t_command *cmd);
void						buildin_export(t_command *cmd);
void						buildin_pwd(t_command *cmd);
void						buildin_env(t_command *cmd);
void						buildin_cd(t_command *cmd);
void						buildin_cd_cut(t_command *cmd, t_env *home);
void						buildin_echo(t_command *cmd);
int							buildin_exit(t_command *cmd);

#endif