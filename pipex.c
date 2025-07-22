/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/07/22 11:55:43 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

int	is_last(int i, int count)
{
	if (i == count - 1)
		return (1);
	return (0);
}

void	run_command(char *str, t_pipex ctx, char *envp[])
{
	char	*command;
	char	*pathname;
	char	**args;

	// Parse and execute command
	command = split_command(str);
	args = ft_split(str, ' ');
	//args = split_args(argv);
	pathname = path(command, ctx.paths);
	// If execve fails you should return exit(127) or similar
	if (execve(pathname, args, envp) == -1)
	{
		free(command);
		free(pathname);
		free_arr_str(args);
	}
}
void	child_process(int i, t_pipex ctx, char *command, char *envp[])
{
	dup2(ctx.prev_fd, STDIN_FILENO);
	if (is_last(i, ctx.loops))
		dup2(ctx.output_fd, STDOUT_FILENO);
	else
		dup2(ctx.pipefd[1], STDOUT_FILENO);
	close(ctx.prev_fd);
	close(ctx.pipefd[0]);
	close(ctx.pipefd[1]);
	if (is_last(i, ctx.loops))
		close(ctx.output_fd);
	run_command(command, ctx, envp);
}

t_pipex	init_structure(int argc, char *argv[], char *envp[])
{
	t_pipex	p;

	p.loops = argc - 3;
	p.prev_fd = open_input(argv[1]);
	p.output_fd = open_output(argv[argc - 1]);
	p.paths = ft_split(get_path_env(envp), ':');
	return (p);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_pipex	ctx;
	pid_t	pid;

	if (argc < 5)
		return (0);
	i = 0;
	ctx = init_structure(argc, argv, envp);
	while (i < ctx.loops)
	{
		// Create pipe except on last iteration
		if (!is_last(i, ctx.loops) && pipe(ctx.pipefd) == -1)
			return (1);
		pid = fork();
		// CHILD PROCESS
		if (pid == 0)
			child_process(i, ctx, argv[i + 2], envp);
		else if (pid < 0)
		{
			// Handle errors
			return (2);
		}
		// PARENT
		close(ctx.prev_fd);
		close(ctx.pipefd[1]);
		ctx.prev_fd = ctx.pipefd[0];
		i++;
	}
	wait_chidren(ctx.loops);
	free_arr_str(ctx.paths);
	return (0);
}
