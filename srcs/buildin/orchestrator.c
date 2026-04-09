/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 01:25:03 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/08 15:04:31 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*search_key_var(t_env *env, char *key)
{
	t_env	*tmp;
	int		len;
	
	len = (ft_strlen(key) + 1);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key_var, len))
			return(tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	what_the_buildin(t_node *node)
{
	if (node->cmd->av[0] == NULL)
		return (0);
	else if (!ft_strncmp(ECHO, node->cmd->av[0], 5)) // 1
		buildin_echo(node->cmd);
	else if (!ft_strncmp(CD, node->cmd->av[0], 3)) // 2
		buildin_cd(node->cmd);
	else if (!ft_strncmp(PWD, node->cmd->av[0], 4)) // 3
		buildin_pwd(node->cmd);
	else if (!ft_strncmp(ENV, node->cmd->av[0], 4)) // 4
		buildin_env(node->cmd);
	else if (!ft_strncmp(EXPORT, node->cmd->av[0], 7)) // 5
		buildin_export(node->cmd);
	else if (!ft_strncmp(UNSET, node->cmd->av[0], 6)) // 6
		buildin_unset(node->cmd);
	else if (!ft_strncmp(EXIT, node->cmd->av[0], 5)) // 7
	{
		if (buildin_exit(node->cmd))
			return (1);
	}
	else
		what_the_separator(node, node->cmd->shell);
	// else
	// 	exec_cmd(node, node->cmd->av, rebuild_env(&node->cmd->shell->env));
	return (0);
}

/* t_shell	*ft_shellnew(void)
{
	t_shell	*element;
	
	element = malloc(sizeof(t_shell));
	if (!element)
		return (NULL);
	element->env = NULL;
	element->exit_status = NULL;
	return (element);
}

int	main(int ac, char **av, char **env)
{
	t_env		*lst_env = NULL;
	t_command	cmd;
	int			i;

	ft_memset(&cmd, 0, (sizeof(t_command)));
	lst_env = call_env(env);
	cmd.shell = ft_shellnew();
	cmd.shell->env = lst_env;

	cmd.ac = ac;
	cmd.av = malloc(sizeof(char *) * ((cmd.ac) + 1));
	i = 0;
	while (i < ac)
	{
		cmd.av[i] = ft_strdup(av[i + 1]);
		i++;
	}
	what_the_buildin(&cmd);
	return (0);
}
 */
