/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusquer <mmusquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:54:22 by mvignes           #+#    #+#             */
/*   Updated: 2026/04/30 17:15:41 by mmusquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief execute the node left
/// @param node 
/// @param pipe 
static void	exec_left(t_node *node, t_shell *shell, int *pipe)
{
	shell->forking = 1;
	close(pipe[0]);
	redirect_fd(STDOUT_FILENO, pipe[1]);
	close(pipe[1]);
	node->left->in_pipe = true;
	exec_node(node->left);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit_free_all(shell->free_the_token, shell->free_the_node, shell, NULL);
}

/// @brief execute the node right
/// @param node 
/// @param pipe 
static void	exec_right(t_node *node, t_shell *shell, int *pipe)
{
	shell->forking = 1;
	close(pipe[1]);
	redirect_fd(STDIN_FILENO, pipe[0]);
	close(pipe[0]);
	exec_node(node->right);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit_free_all(shell->free_the_token, shell->free_the_node, shell, NULL);
}

/// @brief execute the "|" and do a recursive if there are other
/// separators after
/// @param node 
/// @return exit_status
int	exec_pipe(t_node *node)
{
	int		pipe[2];
	int		status;
	pid_t	pid_left;
	pid_t	pid_right;

	if (create_pipe(pipe))
		error_message("error : during the creation of the pipe\n");
	pid_left = create_fork();
	if (pid_left == 0)
		exec_left(node, call_shell(node), pipe);
	pid_right = create_fork();
	if (pid_right == 0)
		exec_right(node, call_shell(node), pipe);
	close(pipe[0]);
	close(pipe[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	search_exit_status(call_shell(node), status, false);
	return (call_shell(node)->exit_status);
}
