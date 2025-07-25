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

/* Initializes context. For each command:
- Creates pipe
- Calls `fork_process` to create a new process
- Once the loop is finished, the parent calls `cleanup`*/
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
		create_pipe(i, &ctx);
		fork_process(&i, &ctx);
	}
	pipex_cleanup(ctx);
	return (0);
}
