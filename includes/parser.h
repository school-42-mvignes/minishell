/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:55:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/21 16:00:31 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_node		t_node;
typedef struct s_token		t_token;
typedef struct s_redir		t_redir;
typedef struct s_command	t_command;
typedef struct s_shell		t_shell;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
}							t_node_type;

t_node						*parse_and_or(t_token **token, t_shell *shell);
t_node						*parse_pipe(t_token **token, t_shell *shell);
t_node						*parse_cmd(t_token **token, t_shell *shell);
t_redir						*parse_redir(t_token **token);
t_node						*parse_bracket(t_token **token, t_shell *shell);
void						free_malloc_fail(t_node *node, t_command *cmd);

t_token						*use_token(t_token **token);
t_redir						*add_redir(t_redir **redir, t_redir *new_redir);
int							count_word(t_token *tmp);
void						while_redir(t_token **token, t_command *cmd);
void						skip_spaces(t_token **token);
void						free_node(t_node *node);
int							is_word_quote_redir(t_token *token);

#endif
