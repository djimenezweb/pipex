/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/06/24 12:47:06 by danielji         ###   ########.fr       */
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
	int	fd[2];
	pid_t	pid1;
	pid_t	pid2;

	char *command;
	char *fullcommand;
	char **args;

	int fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
	{
		// Manage errors
	}
	int fd_out = open(argv[4], O_RDWR|O_CREAT, 0666);
	if (fd_out == -1)
	{
		// Manage errors
	}

	if (pipe(fd) == -1)
		return (1);

	// CHILD PROCESS 1
	pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		command = split_command(argv[2]);
		fullcommand = path(command, envp);
		args = ft_split(argv[2], ' ');
		//args = split_args(argv[2]);
		execve(fullcommand, args, NULL);
		free(command);
		free(fullcommand);
		free_arr_str(args);
	}

	// CHILD PROCESS 2
	pid2 = fork();
	if (pid2 < 0)
		return 3;
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		command = split_command(argv[3]);
		fullcommand = path(command, envp);
		args = ft_split(argv[3], ' ');
		//args = split_args(argv[3]);
		execve(fullcommand, args, NULL);
		free(command);
		free(fullcommand);
		free_arr_str(args);
	}

	close(fd[0]);
	close(fd[1]);
	close(fd_in);
	close(fd_out);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}
