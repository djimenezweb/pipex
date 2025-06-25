/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/06/25 13:15:49 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

int	is_last(int i, int count)
{
	if (i == count - 1)
		return (1);
	return (0);
}

void	run_command(char *str, t_pipex p, char *envp[])
{
	char	*command;
	char	*pathname;
	char	**args;

	// Parse and execute command
	command = split_command(str);
	args = ft_split(str, ' ');
	//args = split_args(argv);
	pathname = path(command, p.paths);
	// If execve fails you should return exit(127) or similar
	if (execve(pathname, args, envp) == -1)
	{
		free(command);
		free(pathname);
		free_arr_str(args);
	}
}

void	child_process(int i, t_pipex p, char *command, char *envp[])
{
	dup2(p.prev_fd, STDIN_FILENO);
	if (is_last(i, p.loops))
		dup2(p.output_fd, STDOUT_FILENO);
	else
		dup2(p.fd[1], STDOUT_FILENO);
	close(p.prev_fd);
	close(p.fd[0]);
	close(p.fd[1]);
	if (is_last(i, p.loops))
		close(p.output_fd);
	run_command(command, p, envp);
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
	t_pipex	p;
	pid_t	pid;

	if (argc < 5)
		return (0);
	i = 0;
	p = init_structure(argc, argv, envp);
	while (i < p.loops)
	{
		// Create pipe except on last iteration
		if (!is_last(i, p.loops) && pipe(p.fd) == -1)
			return (1);
		pid = fork();
		// CHILD PROCESS
		if (pid == 0)
			child_process(i, p, argv[i + 2], envp);
		else if (pid < 0)
		{
			// Handle errors
			return (2);
		}
		// PARENT
		close(p.prev_fd);
		close(p.fd[1]);
		p.prev_fd = p.fd[0];
		i++;
	}
	wait_chidren(p.loops);
	free_arr_str(p.paths);
	return (0);
}
