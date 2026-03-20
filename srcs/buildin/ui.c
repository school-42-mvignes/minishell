/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:06:29 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/20 01:17:41 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

// LA SAINTE COMMANDE : cc ui.c ../libft/ft_strncmp.c ../libft/ft_strdup.c ../libft/ft_strlen.c ../libft/ft_putchar_fd.c ../libft/ft_putendl_fd.c ../libft/ft_putstr_fd.c ../utils/print_struc.c ../exec/ttest.c ../libft/ft_lstnew.c ../libft/ft_lstadd_back.c ../libft/ft_lstlast.c ../libft/ft_memset.c ../libft/ft_strchr.c ../libft/ft_strlcpy.c ../libft/ft_free_tab.c ../libft/ft_lstclear.c ../libft/ft_lstdelone.c ../libft/ft_substr.c ../libft/get_next_line_utils.c ../libft/ft_strjoin.c ../utils/lstenv.c ../utils/other_split.c ../libft/ft_calloc.c -g3


/*						quand je dis fait il y aura surement des choses a faire derniere comme modifier pour mettre une redir >>>
echo		1 // fait
cd			2 
pwd			3 // fait
env			4 // fait
export		5 // a tester quand on aura un minishell avec readline
unset		6 // fait
exit		7 
*/

void	buildin_echo(t_command *cmd) // 1
{
	int	i;

	i = 1;
	if (!ft_strncmp("-n", cmd->av[1], 3))
		i++;
	while (cmd->av[i])
	{
		if (i != 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmd->av[i++], 1);
	}
	if (ft_strncmp("-n", cmd->av[1], 3))
		ft_putchar_fd('\n', 1);
	return ;
}

void	buildin_cd(t_command *cmd) // 2
{
	
}

void	buildin_env(t_command *cmd) // 3
{
	printf_env(cmd->shell->env);
}

void	buildin_pwd(t_command *cmd) // 4
{
	t_env	*tmp;

	tmp = cmd->shell->env;
	while (ft_strncmp("PWD", tmp->key_var, 4))
		tmp = tmp->next;
	if (!ft_strncmp("PWD", tmp->key_var, 4))
		ft_putendl_fd(tmp->var, 1);
}


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


void	buildin_export(t_command *cmd) // 5 // a tester quand on aura un minishell avec readline
{
	t_env	*node;
	char	**tab;

	tab = split_in_two(cmd->av[1], '=');
	if (!tab)
		return ;
	node = search_key_var(cmd->shell->env, tab[0]);
	if (!node)
	{
		node = ft_envnew(tab);
		ft_envadd_back(&cmd->shell->env, node);
		free(tab);
	}
	else
	{
		free(tab[0]);
		free(node->var);
		node->var = NULL;
		node->var = tab[1];
		free(tab);
	}
	printf_env(cmd->shell->env);
}

static void	ft_delete_envnode(t_env *preview_node, t_env *node)
{
	preview_node->next = node->next;
	free(node->key_var);
	node->key_var = NULL;
	free(node->var);
	node->var = NULL;
}

// ca fonction mais peut etre faire quelques chose de plus propre, mais en vrai flemme cest deja pas mal
void	buildin_unset(t_command *cmd) // 6
{
	t_env	*tmp;
	t_env	*preview;
	int		len;
	
	len = (ft_strlen(cmd->av[1]) + 1);
	tmp = cmd->shell->env;
	while (tmp)
	{
		if (!ft_strncmp(cmd->av[1], tmp->key_var, len))
		{
			ft_delete_envnode(preview, tmp);
			break;
		}
		// printf("\033[0;35m\033[1mcmd av[0] = {%s}, tmp keyvar = {%s}, tmp var = {%s}, strlen = {%d}\n\033[0m", cmd->av[1], tmp->key_var, tmp->var, i);
		preview = tmp;
		tmp = tmp->next;
	}
	printf_env(cmd->shell->env);
}

void	buildin_exit(t_command *cmd) // 7
{
	// fonction pour finir en BEAUTÉ
}

void	what_the_buildin(t_command *cmd)
{
	if (!ft_strncmp("echo", cmd->av[0], 5)) // 1
		buildin_echo(cmd);
	if (!ft_strncmp("cd", cmd->av[0], 3)) // 2
		buildin_cd(cmd);
	if (!ft_strncmp("pwd", cmd->av[0], 4)) // 3
		buildin_pwd(cmd);
	if (!ft_strncmp("env", cmd->av[0], 4)) // 4
		buildin_env(cmd);
	if (!ft_strncmp("export", cmd->av[0], 7)) // 5
		buildin_export(cmd);
	if (!ft_strncmp("unset", cmd->av[0], 6)) // 6
		buildin_unset(cmd);
	if (!ft_strncmp("exit", cmd->av[0], 5)) // 7
		buildin_exit(cmd);
	return ;
}

t_shell	*ft_shellnew(void)
{
	t_shell	*element;
	
	element->i = 0;

	element = malloc(sizeof(t_shell));
	if (!element)
		return (NULL);
	element->env = NULL;
	element->exit_status = NULL;
	return (element);
}

char	*test_de_salaupard(void)
{
	char	*oui;

	oui = malloc(sizeof(char *) * 1);
	oui[0] = '\0';
	return (oui);
}

int	main(int ac, char **av, char **env)
{
	t_env		*lst_env = NULL;
	t_command	cmd;
	int			i;

	memset(&cmd, 0, (sizeof(t_command)));
	lst_env = call_env(env);
	cmd.shell = ft_shellnew();
	cmd.shell->env = lst_env;
	// printf_env(cmd.shell->env);

	cmd.ac = ac;
	cmd.av = malloc(sizeof(char *) * ((cmd.ac) + 1));
	i = 0;
	// printf("ac = %i\n", ac);
	while (i < ac)
	{
		cmd.av[i] = ft_strdup(av[i + 1]);
		// printf("cmd.av[%i] = %s\n", i, cmd.av[i]);
		i++;
	}
	// if (ac > 1)
	what_the_buildin(&cmd);
	// char * salaudpard = test_de_salaupard();
	// if (!salaudpard)
	// 	printf("ca va etre chiant\n");
	// if (salaudpard[0] == '\0')
	// 	printf("si tu es solo mon salaud tu es un tigre\n");
	// printf("EH OUI MON SALAUD = {%s}\n", salaudpard);
	return (0);
}




/* t_env	*search_key_var(t_env *env, char *key)
{
	t_env	*tmp;
	int		i;
	
	i = (ft_strlen(key) + 1);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key_var, i))
			break;
		// printf("\033[0;35m\033[1mcmd av[0] = {%s}, tmp keyvar = {%s}, tmp var = {%s}, strlen = {%d}\n\033[0m", cmd->av[1], tmp->key_var, tmp->var, i);
		tmp = tmp->next;
	}
	return (tmp);
}

void	buildin_unset(t_command *cmd) // 6
{
	t_env	*tmp;
	t_env	*preview;
	int		i;
	
	i = (ft_strlen(cmd->av[1]) + 1);
	tmp = cmd->shell->env;
	while (tmp)
	{
		if (!ft_strncmp(cmd->av[1], tmp->key_var, i))
		{
			ft_delete_envnode(preview, tmp);
			break;
		}
		// printf("\033[0;35m\033[1mcmd av[0] = {%s}, tmp keyvar = {%s}, tmp var = {%s}, strlen = {%d}\n\033[0m", cmd->av[1], tmp->key_var, tmp->var, i);
		preview = tmp;
		tmp = tmp->next;
	}
	printf_env(cmd->shell->env);
} */