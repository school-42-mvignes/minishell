/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:55:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 20:09:05 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
}					t_node_type;

typedef struct s_redir
{
	char				*file;
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
	bool			is_subshell;
	t_redir			*redir;
	t_shell			*shell;
}					t_command;

typedef struct s_node
{
	t_node_type		type;
	t_command		*cmd;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;


t_token				*use_token(t_token **token);

t_node				*parse_and_or(t_token **token);
t_node				*parse_pipe(t_token **token);
t_node				*parse_cmd(t_token **token);

#endif
