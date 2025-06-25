/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/06/25 11:32:17 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	run_command(char *str, char *envp[])
{
	char	*command;
	char	*pathname;
	char	**args;

	// Parse and execute command
	command = split_command(str);
	args = ft_split(str, ' ');
	//args = split_args(argv);
	pathname = path(command, envp);
	// If execve fails you should return exit(127) or similar
	if (execve(pathname, args, envp) == -1)
	{
		free(command);
		free(pathname);
		free_arr_str(args);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		prev_fd;
	int		output_fd;
	pid_t	pid;
	int		fd[2];

	if (argc < 5)
		return (0);
	i = 0;
	prev_fd = open_input(argv[1]);
	output_fd = open_output(argv[argc - 1]);
	while (i < argc - 3)
	{
		// Don't create pipe on the last iteration
		if (i != (argc - 3) - 1)
			if (pipe(fd) == -1)
				return (1);
		pid = fork();
		// CHILD PROCESS
		if (pid == 0)
		{
			dup2(prev_fd, STDIN_FILENO);
			if (i == (argc - 3) - 1)
				dup2(output_fd, STDOUT_FILENO);
			else
				dup2(fd[1], STDOUT_FILENO);
			close(prev_fd);
			close(fd[0]);
			close(fd[1]);
			if (i == (argc - 3) - 1)
				close(output_fd);
			run_command(argv[i + 2], envp);
		}
		else if (pid < 0)
		{
			// Handle errors
			return (2);
		}
		// PARENT
		close(prev_fd);
		close(fd[1]);
		prev_fd = fd[0];
		i++;
	}
	wait_chidren(argc - 3);
	return (0);
}
