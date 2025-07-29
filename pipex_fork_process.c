/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fork_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:06:19 by danielji          #+#    #+#             */
/*   Updated: 2025/07/28 08:43:53 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Creates a pipe. Exits program on error. */
static void	create_pipe(t_pipex *ctx)
{
	if (pipe(ctx->pipefd) == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

/* Closes fds, assigns read end of pipe to `prev_fd` for the next iteration */
static void	cleanup_parent(int i, t_pipex *ctx)
{
	close(ctx->prev_fd);
	if (!is_last(i, ctx->loops))
	{
		close(ctx->pipefd[1]);
		ctx->prev_fd = ctx->pipefd[0];
	}
	else
	{
		close(ctx->outfile_fd);
		if (ctx->paths)
			free_arr_str(ctx->paths);
	}
}

/* Creates a pipe (except on last iteration). Forks new process.
Child runs comand, parent closes fds. Returns child's pid. */
pid_t	fork_process(int i, t_pipex *ctx)
{
	pid_t	pid;
	char	*command;
	char	*pathname;
	char	**args;

	if (!is_last(i, ctx->loops))
		create_pipe(ctx);
	command = split_command(ctx->argv[i + 2]);
	if (command[0] == '\0')
	{
		free(command);
		exit(127);
	}
	args = ft_split(ctx->argv[i + 2], ' ');
	pathname = get_command_path(command, ctx->paths);

	if (pathname[0] == '\0')
		print_cmd_not_found(command);
	pid = fork();
	// CHILD PROCESS
	if (pid == 0)
	{
		redirect_stdio(i, *ctx);
		cleanup_child(i, *ctx);
		if (pathname[0] == '\0' || (i == 0 && ctx->infile_fd < 0))
			exit(127);
		if (execve(pathname, args, ctx->envp) == -1)
			exit(127);
	}
	else if (pid < 0)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	free(command);
	free(pathname);
	free_arr_str(args);
	cleanup_parent(i, ctx);
	return (pid);
}
