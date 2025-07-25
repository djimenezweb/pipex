/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/07/25 10:52:46 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

/* Waits for children, frees allocated memory, closes open file descriptors. */
void	pipex_cleanup(t_pipex ctx)
{
	wait_chidren(ctx.loops);
	free_arr_str(ctx.paths);
	close(ctx.pipefd[0]);
	close(ctx.outfile_fd);
}

static void	advance_pipeline(int *i, t_pipex *ctx)
{
	close(ctx->prev_fd);
	close(ctx->pipefd[1]);
	ctx->prev_fd = ctx->pipefd[0];
	(*i)++;
}

void	fork_process(int *i, t_pipex *ctx, char *argv[])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		// CHILD PROCESS
		run_pipeline_child(*i, *ctx, argv[*i + 2]);
	}
	else if (pid < 0)
	{
		// PARENT (ERRORS)
		// Handle errors
		// return (2);
	}
	else if (pid > 0)
	{
		// PARENT
		advance_pipeline(i, ctx);
	}
}

/* - Initializes context
- Creates a pipe except on last iteration
- Creates a new process with `fork()`
- The child runs the command
- The parent closes file descriptors
- The output of the previous command becomes the input of the next.
- Outside the loop, the parent waits */
int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_pipex	ctx;

	if (argc < 5)
		return (0);
	i = 0;
	ctx = init_context(argc, argv, envp);
	while (i < ctx.loops)
	{
		if (!is_last(i, ctx.loops) && pipe(ctx.pipefd) == -1)
			return (1);
		if (i == 0 && ctx.infile_fd < 0)
		{
			advance_pipeline(&i, &ctx);
			continue ;
		}
		fork_process(&i, &ctx, argv);
	}
	pipex_cleanup(ctx);
	return (0);
}
