/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/07/30 13:27:03 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Prints error message and exits program */
void	bad_args(void)
{
	printerror(-1, "Bad arguments. Usage:");
	printerror(-1, "./pipex infile cmd1 cmd2 outfile");
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		status;
	t_pipex	ctx;

	if (argc != 5)
		bad_args();
	i = 0;
	ctx = init_context(argc, argv, envp);
	while (i < ctx.loops)
	{
		ctx.pids[i] = fork_process(i, &ctx);
		i++;
	}
	i = 0;
	while (i < ctx.loops)
	{
		waitpid(ctx.pids[i], &status, 0);
		i++;
	}
	free_context(ctx, 0);
	return (WEXITSTATUS(status));
}
