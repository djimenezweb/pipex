/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fork_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:06:19 by danielji          #+#    #+#             */
/*   Updated: 2025/07/29 19:50:25 by danielji         ###   ########.fr       */
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
		close(ctx->outfile_fd);
}

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
	{
		// free stuff
		//free(command);
		exit(127);
	}
	if (ctx->exec_paths[i][0] == '\0')
		print_cmd_not_found(command);
	pid = fork();
	// CHILD PROCESS
	if (pid == 0)
	{
		redirect_stdio(i, *ctx);
		cleanup_child(i, *ctx);
		if (ctx->exec_paths[i][0] == '\0' || (i == 0 && ctx->infile_fd < 0))
			exit(127);
		if (execve(ctx->exec_paths[i], ctx->args[i], ctx->envp) == -1)
			exit(127);
	}
	else if (pid < 0)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	cleanup_parent(i, ctx);
	return (pid);
}
