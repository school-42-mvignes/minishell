/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:55:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 18:54:34 by mmusquer         ###   ########.fr       */
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
	NONE,       // y'a R
}						t_type;

typedef struct s_token
{
	t_type				type;
	char				*value; 
	struct s_token		*next;
}						t_token;

/*LEXER*/

t_token					*create_token(t_type token, char *value, int n);
t_token					*add_token(t_token **lst, t_token *new_nod);
t_token					*lexer(char *str, t_token *token);

/*LEXER UTILS*/
int						lexer_quote(t_token *token, char *str, int i, int j);
int						lexer_sep1(t_token *token, char *str, int i);
int						lexer_sep2(t_token *token, char *str, int i);
int						lexer_sep3(t_token *token, char *str, int i);
int						lexer_word(t_token *token, char *str, int i);
void					free_token_lst(t_token *lst);

#endif
