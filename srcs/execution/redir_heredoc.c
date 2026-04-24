/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:57:48 by mmusquer          #+#    #+#             */
/*   Updated: 2026/04/24 14:24:28 by mmusquer         ###   ########.fr       */
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
			ft_putstr_fd("minishell: warning: here-document ", 2);
			ft_putstr_fd("at line 21 delimited by end-of-file (wanted '", 2);
			ft_putstr_fd(lim, 2);
			ft_putstr_fd("')\n", 2);
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
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	do_heredoc_while(lim, shell, flag, fd);
	close(fd[1]);
	exit(0);
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
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		close(fd[0]);
		g_status = SIGINT;
		return (-1);
	}
	return (fd[0]);
}
