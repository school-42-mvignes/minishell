/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:55:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/30 09:38:53 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # define DEFAULT_SOURCES
# include "libft.h"
# include <stdbool.h>
# include "buildin.h"
# include "env.h"
# include "lexer.h"
# include <signal.h>
# include "execution.h"
# include "expand.h"
# include "lexer.h"
# include "parser.h"
# include <math.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>
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
	struct termios	termios_save;
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

t_shell		*call_shell(t_node *node);
void		init_signal(void);
void		controller(int sig);
void		heredoc_controller(int sig);
void		exit_free_all(t_token *lst, t_node *node, t_shell *shell, char *b);

int			main(int ac, char **av, char **env);
int			verif_rl(t_token *cur, t_node *node, t_shell *shell, char *buf);
int			do_lexer(t_token **cur, t_token *token, t_shell *shell, char *buf);
int			do_parser(t_token **cur, t_node **node, t_shell *shell, char *buf);
void		end_while(t_node **node, t_token **cur, t_shell *shell, char *buf);

#endif
