/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:55:28 by danielji          #+#    #+#             */
/*   Updated: 2025/07/26 17:10:29 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Redirects input from previous fd and output to pipeline's write end.
On last iteration, output is instead redirected to outfile */
static void	redirect_stdio(int i, t_pipex ctx)
{
	dup2(ctx.prev_fd, STDIN_FILENO);
	if (is_last(i, ctx.loops))
		dup2(ctx.outfile_fd, STDOUT_FILENO);
	else
		dup2(ctx.pipefd[1], STDOUT_FILENO);
}

/* Closes fds. On last iteration, closes outfile fd */
static void	cleanup_child(int i, t_pipex ctx)
{
	close(ctx.prev_fd);
	if (!is_last(i, ctx.loops))
	{
		close(ctx.pipefd[0]);
		close(ctx.pipefd[1]);
	}
	if (is_last(i, ctx.loops))
		close(ctx.outfile_fd);
}

/* Sets up input/output redirection, closes fds, and runs the command. */
/* TO DO: WHAT IF THERE'S NO COMMAND TO RUN???? */
void	run_pipeline_child(int i, t_pipex ctx)
{
	char	*command;
	char	*pathname;
	char	**args;

	redirect_stdio(i, ctx);
	cleanup_child(i, ctx);
	command = split_command(ctx.argv[i + 2]);
	args = ft_split(ctx.argv[i +2], ' ');
	pathname = get_command_path(command, ctx.paths);
	if (execve(pathname, args, ctx.envp) == -1)
	{
		free(command);
		free(pathname);
		free_arr_str(args);
		exit(127);
	}
}
