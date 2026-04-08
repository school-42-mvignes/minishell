/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 04:03:34 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/30 21:29:31 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include <stdbool.h>

typedef struct s_env
{
	char				*key_var;
	char				*var;
	struct s_env		*next;
}						t_env;

// void				call_env(t_env	**lst_env, char **env);
t_env			*call_env(char **env);
char			**rebuild_env(t_env **env);

// srcs/utils/
void			printf_env(t_env *lst);
void			printf_list(t_list *lst);
char			**split_in_two(char *str, char c);
void			split_tab_to_list(char **old_tab, t_list **lst);

// liste_chainer
t_env			*ft_envnew(char **tab);
int				ft_envsize(t_env *env);
t_env			*ft_envlast(t_env *lst);
void			ft_envclear(t_env **env, void (*del)(void *));
void			ft_envadd_back(t_env **lst, t_env *new);

#endif