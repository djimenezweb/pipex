/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:55:28 by danielji          #+#    #+#             */
/*   Updated: 2025/07/29 19:50:25 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Sets up input/output redirection, closes fds, and runs the command.
void	run_pipeline_child(int i, t_pipex ctx)
{
	char	*command;
	char	*pathname;
	char	**args;

	if (i == 0 && ctx.infile_fd < 0)
	{
		// handle invalid infile
		exit(127);
	}
	redirect_stdio(i, ctx);
	cleanup_child(i, ctx);

	if (pathname[0] == '\0' || execve(pathname, args, ctx.envp) == -1)
	{
		free(command);
		free(pathname);
		free_arr_str(args);
		exit(127);
	}
}*/
