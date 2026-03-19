/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 20:55:48 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/19 11:09:14 by mmusquer         ###   ########.fr       */
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
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include "lexer.h"

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

#endif
