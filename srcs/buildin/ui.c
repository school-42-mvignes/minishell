/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:06:29 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/25 14:39:04 by mvignes          ###   ########.fr       */
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

// # ifndef BUILDIN
#  define ECHO "echo"		// 1
#  define CD "cd"			// 2
#  define PWD "pwd"			// 3
#  define ENV "env"			// 4
#  define EXPORT "export"	// 5
#  define UNSET "unset"		// 6
#  define EXIT "exit"		// 7
// # endif
#  define OLD_PWD "OLDPWD"			// 3


// Pour la fonction du dessous, envoyé la redirection pour savoir ou l'écrire // ou faire en sorte que cela retourne quelque chose de cette fonctions
void	what_the_buildin(t_command *cmd)
{
	if (!ft_strncmp(ECHO, cmd->av[0], 5)) // 1
		buildin_echo(cmd);
	if (!ft_strncmp(CD, cmd->av[0], 3)) // 2
		buildin_cd(cmd);
	if (!ft_strncmp(PWD, cmd->av[0], 4)) // 3
		buildin_pwd(cmd);
	if (!ft_strncmp(ENV, cmd->av[0], 4)) // 4
		buildin_env(cmd);
	if (!ft_strncmp(EXPORT, cmd->av[0], 7)) // 5
		buildin_export(cmd);
	if (!ft_strncmp(UNSET, cmd->av[0], 6)) // 6
		buildin_unset(cmd);
	if (!ft_strncmp(EXIT, cmd->av[0], 5)) // 7
		buildin_exit(cmd);
	return ;
}

t_shell	*ft_shellnew(void)
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

	memset(&cmd, 0, (sizeof(t_command)));
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
	// if (ac > 1)
	what_the_buildin(&cmd);
	return (0);
}
