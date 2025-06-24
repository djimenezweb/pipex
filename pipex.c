/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/06/24 20:25:42 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"
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
	int		prev_fd = -1;
	int		input_fd;
	int		output_fd;
	int		i;
	pid_t	pid;
	
	i = 0;
	loops = argc - 3;
	input_fd = open(argv[1], O_RDONLY);
	if (input_fd == -1)
	{
		// Manage errors
	}
	output_fd = open(argv[argc - 1], O_RDWR|O_CREAT, 0666);
	if (output_fd == -1)
	{
		// Manage errors
	}
	
	while (i < loops)
	{
		int		fd[2];
		char	*command;
		char	*fullcommand;
		char	**args;

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
			
			// Close unused fd
			/*close(fd[0]);
			if (prev_fd != -1)
				close(prev_fd);
			if (i != loops - 1)
			{
				close(fd[1]);
			} */

			// Parse and execute command
			command = split_command(argv[i + 2]);
			fullcommand = path(command, envp);
			args = ft_split(argv[i + 2], ' ');
			ft_printf("Loop %d: %s", i, fullcommand);
			//args = split_args(argv[i + 2]);
			execve(fullcommand, args, envp);
			//close(fd[0]);
			//close(fd[1]);
			free(command);
			free(fullcommand);
			free_arr_str(args);
		}
		// PARENT
		if (prev_fd != -1)
			close(prev_fd);
		if(i < loops - 1)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		close(input_fd);
		i++;
	}
	// Wait
	i = 0;
	while(i < loops)
	{
		wait(NULL);
		i++;
	}
	close(output_fd);
	return (0);
}
