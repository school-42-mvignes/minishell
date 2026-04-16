/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:01 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/15 16:46:18 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief find the path in the environment
/// @param envp 
/// @return reviews the path or returns null if it is not found
char	*search_my_path(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/// @brief assemble the path with the command
/// @param path 
/// @param cmd 
/// @return return the command whith the path
char	*build_my_path(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	if (!full_path)
		return (free(tmp), NULL);
	free(tmp);
	return (full_path);
}

/// @brief finds the correct path to execute the command
/// @param cmd 
/// @param envp 
/// @return returns the correct path or NULL if he doesn’t find it
char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*good_dir;
	char	**tab_path;
	char	*path_env;

	if (!cmd || !envp)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = search_my_path(envp);
	if (!path_env)
		return (NULL);
	tab_path = ft_split(path_env, ':');
	if (!tab_path)
		return (NULL);
	i = -1;
	while (tab_path[++i])
	{
		good_dir = build_my_path(tab_path[i], cmd);
		if (good_dir && access(good_dir, X_OK) == 0)
			return (free_tab(tab_path), good_dir);
		free(good_dir);
	}
	return (free_tab(tab_path), NULL);
}
