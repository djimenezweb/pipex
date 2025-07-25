/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/07/25 11:20:35 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

/* - Waits for children
- Frees allocated memory
- Closes open file descriptors */
void	pipex_cleanup(t_pipex ctx)
{
	wait_chidren(ctx.loops);
	free_arr_str(ctx.paths);
	close(ctx.pipefd[0]);
	close(ctx.outfile_fd);
}

/* - Closes open file descriptors
- The output of the previous command becomes the input of the next
- Advances `i` */
static void	advance_pipeline(int *i, t_pipex *ctx)
{
	close(ctx->prev_fd);
	close(ctx->pipefd[1]);
	ctx->prev_fd = ctx->pipefd[0];
	(*i)++;
}

/* Creates a new process
- The child runs the command
- The parent closes file descriptors
- Calls `advance_pipeline` */
void	fork_process(int *i, t_pipex *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		// CHILD PROCESS
		run_pipeline_child(*i, *ctx);
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

/* Initializes context. For each command:
- Creates a pipe except on last iteration
- If there is no infile on first iteration, skips to next command
- Calls `fork_process` to create a new process

Once the loop is finished, the parent calls `cleanup`*/
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
		fork_process(&i, &ctx);
	}
	pipex_cleanup(ctx);
	return (0);
}
