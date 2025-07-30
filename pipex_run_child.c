/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:55:28 by danielji          #+#    #+#             */
/*   Updated: 2025/07/29 19:50:25 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Redirects input from previous fd and output to pipeline's write end.
On last iteration, output is instead redirected to outfile */
void	redirect_stdio(int i, t_pipex ctx)
{
	dup2(ctx.prev_fd, STDIN_FILENO);
	if (is_last(i, ctx.loops))
		dup2(ctx.outfile_fd, STDOUT_FILENO);
	else
		dup2(ctx.pipefd[1], STDOUT_FILENO);
}

/* Closes fds. On last iteration, closes outfile fd */
void	cleanup_child(int i, t_pipex ctx)
{
	close(ctx.prev_fd);
	if (!is_last(i, ctx.loops))
	{
		close(ctx.pipefd[0]);
		close(ctx.pipefd[1]);
	}
	if (is_last(i, ctx.loops))
		close(ctx.outfile_fd);
}

/* Calls `execve` if executable path is not empty
and if `infile` is valid on the first iteration */
void	exec_child(int i, t_pipex ctx)
{
	if (ctx.exec_paths[i][0] == '\0' || (i == 0 && ctx.infile_fd < 0))
		free_context(ctx, 1);
	if (execve(ctx.exec_paths[i], ctx.args[i], ctx.envp) == -1)
		free_context(ctx, 1);
}
