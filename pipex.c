/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/07/25 09:36:32 by danielji         ###   ########.fr       */
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
	pid_t	pid;

	if (argc < 5)
		return (0);
	i = 0;
	ctx = init_context(argc, argv, envp);
	if (ctx.outfile_fd < 0)
		return (1);
	while (i < ctx.loops)
	{
		if (!is_last(i, ctx.loops) && pipe(ctx.pipefd) == -1)
			return (1);
		if (i == 0 && ctx.infile_fd < 0)
		{
			advance_pipeline(&i, &ctx);
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
			// CHILD PROCESS
			run_pipeline_child(i, ctx, argv[i + 2]);
		}
		else if (pid < 0)
		{
			// PARENT (ERRORS)
			// Handle errors
			return (2);
		}
		else if (pid > 0)
		{
			// PARENT
			advance_pipeline(&i, &ctx);
		}
	}
	pipex_cleanup(ctx);
	return (0);
}
