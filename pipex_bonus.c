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

void	bad_args()
{
	ft_putendl_fd("Bad arguments", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/* - Initializes context.
- The loop creates a pipe, forks process and continues to next iteration
- Once the loop is finished, it waits for all children at the end */
int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_pipex	ctx;

	if (argc < 5)
		bad_args();
	i = 0;
	ctx = init_context(argc, argv, envp);
	while (i < ctx.loops)
		fork_process(&i, &ctx);
	wait_chidren(ctx.loops);
	return (0);
}
