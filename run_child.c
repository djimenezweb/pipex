/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:55:28 by danielji          #+#    #+#             */
/*   Updated: 2025/07/23 09:34:35 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

/* Takes a string that represents a command and executes it.*/
void	run_command(char *str, t_pipex ctx, char *envp[])
{
	char	*command;
	char	*pathname;
	char	**args;

	// Parse and execute command
	command = split_command(str);
	args = ft_split(str, ' ');
	//args = split_args(argv);
	pathname = get_command_path(command, ctx.paths);
	// If execve fails you should return exit(127) or similar
	if (execve(pathname, args, envp) == -1)
	{
		free(command);
		free(pathname);
		free_arr_str(args);
	}
}

/* Sets up input/output redirection for a child process in a pipeline
and executes a command. */
void	run_pipeline_child(int i, t_pipex ctx, char *command, char *envp[])
{
	dup2(ctx.prev_fd, STDIN_FILENO);
	if (is_last(i, ctx.loops))
		dup2(ctx.outfile_fd, STDOUT_FILENO);
	else
		dup2(ctx.pipefd[1], STDOUT_FILENO);
	close(ctx.prev_fd);
	close(ctx.pipefd[0]);
	close(ctx.pipefd[1]);
	if (is_last(i, ctx.loops))
		close(ctx.outfile_fd);
	run_command(command, ctx, envp);
}
