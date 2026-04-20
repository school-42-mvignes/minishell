/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:55:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/15 15:02:23 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

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
	SPACES,      // ' '
	NONE,       // y'a R
}					t_type;

typedef struct s_token
{
	t_type			type;
	int				do_not_expand;
	char			*value;
	struct s_token	*next;
}					t_token;

/*LEXER*/

t_token				*create_token(t_type token, char *value, int n);
t_token				*add_token(t_token **lst, t_token *new_nod, int *status);
t_token				*lexer(char *str, t_token *token);

/*LEXER UTILS*/
int					lexer_quote(t_token *token, char *str, int i);
int					lexer_sep(t_token *token, char *str, int i);
int					lexer_sep_redir(t_token *token, char *str, int i);
int					lexer_sep_bracket(t_token *token, char *str, int i);
int					lexer_word(t_token *token, char *str, int i);
void				free_token_lst(t_token *lst);

/*LEXER CHECKER*/

int					lexer_checker(t_token *token);
t_token				*next_token(t_token *token);
int					is_redir(t_token *token);
int					is_sep(t_token *token);

int					first_sep(t_token *token);
int					last_sep(t_token *token);
int					double_sep(t_token *token);
int					redir_file(t_token *token);

int					is_bracket_balance(t_token *token);
int					is_multi_subshell(t_token *token);
int					is_sep_in_subshell(t_token *token);
int					is_subshell_empty(t_token *token);
int					sep_w_subshell(t_token *token);

#endif
