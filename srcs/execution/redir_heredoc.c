/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvignes <mvignes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:57:48 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/28 13:58:19 by mvignes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_heredoc_whileception(t_shell *shell, char *line, int flag,
		int fd[2])
{
	t_token	tmp;

	ft_memset(&tmp, 0, sizeof(t_token));
	tmp.value = line;
	tmp.type = WORD;
	if (flag == 0)
		search_dollards(&tmp, shell);
	write(fd[1], tmp.value, ft_strlen(tmp.value));
	free(tmp.value);
}

static void	do_heredoc_while(char *lim, t_shell *shell, int flag, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (g_status != SIGINT)
			{
				ft_putstr_fd("minishell: warning: here-document ", 2);
				ft_putstr_fd("at line 21 delimited by end-of-file (wanted '",
					2);
				ft_putstr_fd(lim, 2);
				ft_putstr_fd("')\n", 2);
			}
			break ;
		}
		if ((ft_strncmp(line, lim, ft_strlen(lim)) == 0))
		{
			free(line);
			break ;
		}
		do_heredoc_whileception(shell, line, flag, fd);
		write(fd[1], "\n", 1);
	}
}

static void	do_heredoc_cut(t_shell *shell, char *lim, int flag, int fd[2])
{
	signal(SIGINT, heredoc_controller);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	do_heredoc_while(lim, shell, flag, fd);
	close(fd[1]);
	if (g_status == SIGINT)
		shell->exit_status = 130;
	else
		shell->exit_status = 0;
	exit_free_all(shell->free_the_token, shell->free_the_node, shell, NULL);
}

static void	i_was_missing_a_line(int fd[2])
{
	close(fd[0]);
}

int	do_heredoc(char *lim, t_shell *shell, int flag)
{
	int				fd[2];
	int				status;
	pid_t			pid;
	struct termios	saved;

	tcgetattr(STDIN_FILENO, &saved);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		do_heredoc_cut(shell, lim, flag, fd);
	}
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, controller);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		i_was_missing_a_line(fd);
		g_status = SIGINT;
		return (-1);
	}
	return (fd[0]);
}
