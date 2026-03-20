/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:55:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/19 17:25:18 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Deja dans libft.h
// <fcntl.h>
// <limits.h>
// <stdarg.h>
// <stdint.h>
// <stdio.h>
// <stdlib.h>
// <unistd.h>

# include "libft.h"
# include "env.h"
# include "lexer.h"
# include "buildin.h"
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>

typedef struct s_redir
{
	char				*file;
	t_type				token;
	struct s_redir		*next;
}						t_redir;

typedef struct s_shell
{
	t_env				*env;
	int					*exit_status;
	int					i;
}						t_shell;

typedef struct s_command
{
	int					ac;
	char				**av;
	bool				is_subshell;
	t_redir				*redir;
	t_type				sep;
	t_shell				*shell;
	struct s_command	*next;
}						t_command;

#endif
