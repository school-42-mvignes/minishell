/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:04:01 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 17:15:37 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
