/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fork_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:06:19 by danielji          #+#    #+#             */
/*   Updated: 2025/07/28 08:43:53 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

/* Creates a pipe. Exits program on error. */
static void	create_pipe(t_pipex *ctx)
{
	if (pipe(ctx->pipefd) == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

/* Closes fds, assigns read end of pipe to `prev_fd` for the next iteration */
static void	cleanup_parent(int *i, t_pipex *ctx)
{
	close(ctx->prev_fd);
	if (!is_last(*i, ctx->loops))
	{
		close(ctx->pipefd[1]);
		ctx->prev_fd = ctx->pipefd[0];
	}
	else
	{
		close(ctx->outfile_fd);
		free_arr_str(ctx->paths);
	}
	(*i)++;
}

/* Creates a pipe (except on last iteration). Forks new process.
Child runs comand, parent closes fds */
void	fork_process(int *i, t_pipex *ctx)
{
	pid_t	pid;

	if (!is_last(*i, ctx->loops))
		create_pipe(ctx);
	pid = fork();
	if (pid == 0)
		run_pipeline_child(*i, *ctx);
	else if (pid < 0)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	cleanup_parent(i, ctx);
}
