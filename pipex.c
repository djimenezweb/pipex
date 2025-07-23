/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/07/23 10:43:04 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

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
	while (i < ctx.loops)
	{
		if (!is_last(i, ctx.loops) && pipe(ctx.pipefd) == -1)
			return (1);
		pid = fork();
		// CHILD PROCESS
		if (pid == 0)
			run_pipeline_child(i, ctx, argv[i + 2], envp);
		else if (pid < 0)
		{
			// Handle errors
			return (2);
		}
		// PARENT
		// Before moving to the next command, the parent
		// no longer needs the read end of the previous pipe (prev_fd).
		close(ctx.prev_fd);
		// The parent doesn't need the write end of the current pipe (pipefd[0])
		close(ctx.pipefd[1]);
		// For the next iteration prev_fd should be the read end of the just created pipe.
		// This way the next child can use this as its input (stdin).
		// The output of the previous command becomes the input of the next.
		ctx.prev_fd = ctx.pipefd[0];
		i++;
	}
	wait_chidren(ctx.loops);
	free_arr_str(ctx.paths);
	close(ctx.pipefd[0]);
	close(ctx.outfile_fd);
	return (0);
}
