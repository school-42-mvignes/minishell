/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:25:38 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/10 16:28:17 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

void	expand(t_token *token, t_shell *shell);
void	search_dollards(t_token *token, t_shell *shell);
void	cut_quotes(t_token *token);
void	concatenate(t_token *token);

#endif