/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/07/22 14:55:26 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

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
		// Create pipe except on last iteration
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
		close(ctx.prev_fd);
		close(ctx.pipefd[1]);
		ctx.prev_fd = ctx.pipefd[0];
		i++;
	}
	wait_chidren(ctx.loops);
	free_arr_str(ctx.paths);
	return (0);
}
