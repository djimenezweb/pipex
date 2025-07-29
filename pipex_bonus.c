/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/07/26 17:07:45 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* TO DO */
void	bad_args(void)
{
	ft_putendl_fd("Bad arguments", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		status;
	t_pipex	ctx;

	if (argc < 5)
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
	return (WEXITSTATUS(status));
}
