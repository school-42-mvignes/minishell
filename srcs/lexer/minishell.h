/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:55:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/18 17:15:44 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_type
{
	WORD,       // mot
	SP_AND,     // &&
	SP_OR,      // ||
	SP_PIPE,    // |
	REDIR_IN,   // <
	REDIR_OUT,  // >
	REDIR_APP,  // >>
	REDIR_HERE, // <<
	S_QUOTE,    // ''
	D_QUOTE,    // ""
	L_BRACKET,  // (
	R_BRACKET,  // )
	NONE,       // y'a R
}						t_type;

typedef struct s_redir
{
	char				*file;
	t_type				token;
	struct s_redir		*next;
}						t_redir;

typedef struct s_env
{
	char				*key_var;
	char				*var;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	t_env				*env;
	int					*exit_status;
}						t_shell;

typedef struct s_command
{
	int					ac;
	char				**av;
	// bool				is_subshell;	// ()		// a gerer plutard
	t_redir				*redir;
	t_type				sep;
	t_shell				*shell;
	struct s_command	*next;
}						t_command;

typedef struct s_token
{
	t_type				token;
	int					type;
	char				*value;
	struct s_token		*next;
}						t_token;

/*LEXER*/

t_token					*create_token(t_type token, char *value, int n);
t_token					*add_token(t_token **lst, t_token *new_nod);
t_token					*lexer(char *str, t_token *token);
int						lexer_quote(t_token *token, char *str, int i, int j);
int						lexer_sep1(t_token *token, char *str, int i);
int						lexer_sep2(t_token *token, char *str, int i);
int						lexer_sep3(t_token *token, char *str, int i);
int						lexer_word(t_token *token, char *str, int i);
void					free_token_lst(t_token *lst);

#endif
