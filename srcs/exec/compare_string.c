/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 23:44:59 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/14 00:24:17 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cc compare_string.c ../libft/ft_strncmp.c ../libft/ft_strlen.c 

#include "../../includes/minishell.h"


int	main(int ac, char **av)
{

	if (!av[1] || !av[2])
	{
		printf("tes une merde !\n");
		return (1);
	}

	char	*string1 = av[1];
	char	*string2 = av[2];
	int		len_1 = ft_strlen(string1);
	int		len_2 = ft_strlen(string2);
	int		dif;

	if (len_1 - len_2 == 0)
	{
		dif = ft_strncmp(string1, string2, len_1);
		if (dif == 0)
			printf("\033[0;32mFELICITATION PD\n\033[0m");
		else
			printf("\033[0;33mPROBLEME AVEC LE STRNCMP FRERO\n\033[0m");
	}
	else
		printf("\033[0;31mPROBLEME AVEC LES LEN MON ZINC:%d\n\033[0m", len_1 - len_2);
}