/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fork_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:06:19 by danielji          #+#    #+#             */
/*   Updated: 2025/07/26 17:09:04 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Creates a pipe except on last iteration */
static void	create_pipe(int i, t_pipex *ctx)
{
	if (is_last(i, ctx->loops))
		return ;
	if (pipe(ctx->pipefd) == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

/* All iterations:
- Closes prev_fd WHY???
You are already correctly closing pipefd[0] in every iteration via ctx->prev_fd.

All iterations except last
- Closes pipefd[1] (write end of pipe)
- The output of the previous command becomes the input of the next

Last iteration:
- No pipe was created so no need to close pipefd[0] or pipefd[1]
- Closes outfile_fd
- Frees allocated memory */
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

/* Don't fork process if:
- There's no infile on first iteration
- NOT A VALID COMMAND ????
- Other causes?
- Other causes? */
static int	should_skip_command(int i, t_pipex ctx)
{
	if (i == 0 && ctx.infile_fd < 0)
		return (1);
	return (0);
}

/* fork() cheatsheet:
- `pid == 0`: child
- `pid < 0`: parent (errors)
- `pid > 0`: parent */

/* Checks if a new process should be created.
Creates a new process with `fork`
- Child runs comand
- Parent closes file descriptors */
void	fork_process(int *i, t_pipex *ctx)
{
	pid_t	pid;

	create_pipe(*i, ctx);
	if (!should_skip_command(*i, *ctx))
	{
		pid = fork();
		if (pid == 0)
			run_pipeline_child(*i, *ctx);
		else if (pid < 0)
		{
			perror("pipex");
			exit(EXIT_FAILURE);
		}
	}
	cleanup_parent(i, ctx);
}
