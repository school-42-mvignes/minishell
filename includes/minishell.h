/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:55:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/30 21:43:41 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "env.h"
# include "lexer.h"
# include "buildin.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include "lexer.h"
# include "parser.h"
# include "execution.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_redir
{
	char				*outfile;
	int					outfile_fd;
	t_type				type;
	struct s_redir		*next;
}						t_redir;

typedef struct s_shell
{
	t_env				*env;
	int					*exit_status;
}						t_shell;

typedef struct s_command
{
	char			**av;
	char			*infile;
	int				infile_fd;
	bool			is_subshell;
	t_redir			*redir;
	t_shell			*shell;
}					t_command;

typedef struct s_node
{
	t_node_type		type;
	t_command		*cmd;
	int				count;
	struct s_node	*left;
	struct s_node	*right;
	pid_t			last_pid;
}					t_node;

#endif
