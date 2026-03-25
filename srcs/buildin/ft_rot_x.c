
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:25:03 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/20 01:25:11 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	ft_rotate_char(char c, int n)
{
	int	base;

	if (c >= 'a' && c <= 'z')
		base = 'a';
	else if (c >= 'A' && c <= 'Z')
		base = 'A';
	else
		return (c);
	return ((c - base + n) % 26 + base);
}

void	ft_rot_x(char *str, int n)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		str[i] = ft_rotate_char(str[i], n);
		i++;
	}
}
