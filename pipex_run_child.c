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

/* - Redirects input from previous file descriptor (pipeline).
- Redirects output to pipeline write end (except on last iteration)
- On last iteration, redirects output to the outfile */
static void	redirect_stdio(int i, t_pipex ctx)
{
	dup2(ctx.prev_fd, STDIN_FILENO);
	if (is_last(i, ctx.loops))
		dup2(ctx.outfile_fd, STDOUT_FILENO);
	else
		dup2(ctx.pipefd[1], STDOUT_FILENO);
}

/* - Closes prev_fd
- Closes pipe fds
- On last iteration, closes outfile fd */
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

/* Takes a string that represents a command and executes it.
If execve fails you should return exit(127) or similar
How to deal with arguments?
	args = ft_split(str, ' ');
	args = split_args(argv); */

/* - Sets up input/output redirection for a child process in a pipeline.
- Closes open file descriptors.
- Executes the command. */
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
	// WHAT IF THERE'S NO COMMAND TO RUN????
	if (execve(pathname, args, ctx.envp) == -1)
	{
		free(command);
		free(pathname);
		free_arr_str(args);
		exit(127);
	}
}
