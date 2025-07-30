/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fork_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:06:19 by danielji          #+#    #+#             */
/*   Updated: 2025/07/30 13:33:51 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Creates a pipe. Exits program on error. */
static void	create_pipe(t_pipex *ctx)
{
	if (pipe(ctx->pipefd) == -1)
		perror_and_exit();
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
		close(ctx->outfile_fd);
}

/* Creates a pipe (except on last iteration). Forks new process.
Child runs comand, parent closes fds. Returns child's pid. */
pid_t	fork_process(int i, t_pipex *ctx)
{
	pid_t	pid;
	char	*command;

	if (!is_last(i, ctx->loops))
		create_pipe(ctx);
	command = ctx->args[i][0];
	if (command[0] == '\0')
		free_context(*ctx, 1);
	if (ctx->exec_paths[i][0] == '\0')
		print_cmd_not_found(command);
	pid = fork();
	if (pid == 0)
	{
		redirect_stdio(i, *ctx);
		cleanup_child(i, *ctx);
		exec_child(i, *ctx);
	}
	else if (pid < 0)
		perror_and_exit();
	cleanup_parent(i, ctx);
	return (pid);
}
