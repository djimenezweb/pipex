/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/06/25 10:09:37 by danielji         ###   ########.fr       */
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

/* PRUEBAS:
< Makefile grep libft | grep clean > outfile

< Makefile grep libft | tr -d "@" > outfile
./pipex Makefile "grep libft" "tr -d @" outfile
*/
int	main(int argc, char *argv[], char *envp[])
{
	if (argc < 5)
		return (0);
	int		loops;
	int		prev_fd;
	int		input_fd;
	int		output_fd;
	int		i;
	pid_t	pid;
	int		fd[2];
	
	i = 0;
	loops = argc - 3;
	input_fd = open(argv[1], O_RDONLY);
	if (input_fd == -1)
	{
		// Manage errors
	}
	output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
	{
		// Manage errors
	}
	
	while (i < loops)
	{
		if (pipe(fd) == -1)
			return (1);
		pid = fork();
		if (pid < 0)
			return 2;
		if (pid == 0)
		{
			// CHILD PROCESS
			if (i == 0)
				dup2(input_fd, STDIN_FILENO);
			else
				dup2(prev_fd, STDIN_FILENO);
			if (i == loops - 1)
				dup2(output_fd, STDOUT_FILENO);
			else
				dup2(fd[1], STDOUT_FILENO);
			
			// Close no longer needed fd
			if (i != 0)
				close(prev_fd);
			close(fd[0]);
			close(fd[1]);
			if (i == 0)
				close(input_fd);
			if (i == loops - 1)
				close(output_fd);
			run_command(argv[i + 2], envp);
		}
		// PARENT
		if (i != 0)
			close(prev_fd);
		close(fd[1]);
		prev_fd = fd[0];
		i++;
	}
	// Wait
	i = 0;
	while(i < loops)
	{
		wait(NULL);
		i++;
	}
	return (0);
}
