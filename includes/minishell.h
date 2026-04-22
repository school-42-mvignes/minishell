/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:55:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/21 19:19:38 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include "buildin.h"
# include "env.h"
# include "lexer.h"
# include <signal.h>
//# include <X11/keysym.h>
# include "execution.h"
# include "expand.h"
# include "lexer.h"
# include "parser.h"
# include <math.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>

extern int			g_status;
typedef struct s_redir
{
	char			*file;
	int				file_fd;
	int				heredoc_fd;
	int				do_not_expand;
	t_type			type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_shell
{
	t_env			*env;
	t_token			*free_the_token;
	t_node			*free_the_node;
	int				exit_status;
}					t_shell;

typedef struct s_command
{
	char			**av;
	bool			is_subshell;
	t_redir			*redir;
	t_shell			*shell;
}					t_command;

typedef struct s_node
{
	t_node_type		type;
	t_command		*cmd;
	bool			in_pipe;
	int				count;
	struct s_node	*left;
	struct s_node	*right;
	pid_t			last_pid;
}					t_node;

void				init_signal(void);

#endif
