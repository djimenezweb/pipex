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

/* - Closes open file descriptors
- On last iteration only `prev_fd` is closed because no pipe is created
- The output of the previous command becomes the input of the next
- Advances `i` */
static void	advance_pipeline(int *i, t_pipex *ctx)
{
	close(ctx->prev_fd);
	close(ctx->pipefd[1]);
	if (!is_last(*i, ctx->loops))
		ctx->prev_fd = ctx->pipefd[0];
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

	if (should_skip_command(*i, *ctx))
	{
		advance_pipeline(i, ctx);
		return ;
	}
	pid = fork();
	if (pid == 0)
		run_pipeline_child(*i, *ctx);
	else if (pid < 0)
	{
		// Handle errors
	}
	else if (pid > 0)
		advance_pipeline(i, ctx);
}
