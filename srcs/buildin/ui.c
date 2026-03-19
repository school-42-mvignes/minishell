/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:06:29 by mvignes           #+#    #+#             */
/*   Updated: 2026/03/19 14:52:18 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

// LA SAINTE COMMANDE : cc ui.c ../libft/ft_strncmp.c ../libft/ft_strdup.c ../libft/ft_strlen.c ../libft/ft_putchar_fd.c ../libft/ft_putendl_fd.c ../libft/ft_putstr_fd.c ../utils/print_struc.c ../exec/ttest.c ../libft/ft_lstnew.c ../libft/ft_lstadd_back.c ../libft/ft_lstlast.c ../libft/ft_memset.c ../libft/ft_strchr.c ../libft/ft_strlcpy.c ../libft/ft_free_tab.c ../libft/ft_lstclear.c ../libft/ft_lstdelone.c ../libft/ft_substr.c ../libft/get_next_line_utils.c ../libft/ft_strjoin.c ../utils/lstenv.c ../utils/other_split.c -g3


// typedef struct s_command
// {
// 	int					ac;
// 	char				**av;
// 	bool				is_subshell;
// 	t_redir				*redir;
// 	t_type				sep;
// 	t_shell				*shell;
// 	struct s_command	*next;
// }						t_command;

/*
echo		1 // fait
cd			2
pwd			3
env			4
export		5
unset		6
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
	printf("JE SUIS LO\n");
	printf_env(cmd->shell->env);
	printf("JE SUIS LO\n");
}

void	buildin_pwd(t_command *cmd) // 4
{
	
}

void	buildin_export(t_command *cmd) // 5
{
	
}

void	buildin_unset(t_command *cmd) // 6
{
	
}

void	buildin_exit(t_command *cmd) // 7
{
	
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

int	main(int ac, char **av, char **env)
{
	t_env		*lst_env = NULL;
	t_command	cmd;
	int			i;

	
	memset(&cmd, 0, (sizeof(t_command)));
	printf("OUI OUI\n");
	// memset (&cmd.shell->env, 0, (sizeof(t_env)));
	cmd.shell->env = call_env(env);
	printf("BAGUETTE\n");
	// call_env(&cmd.shell->env, env);

	printf("NON\n");

	cmd.ac = ac;
	cmd.av = malloc(sizeof(char *) * ((cmd.ac) + 1));
	i = 0;
	printf("ac = %i\n", ac);
	while (i < ac)
	{
		cmd.av[i] = ft_strdup(av[i + 1]);
		printf("cmd.av[%i] = %s\n", i, cmd.av[i]);
		i++;
	}
	if (ac > 1)
		what_the_buildin(&cmd);
	return (0);
}