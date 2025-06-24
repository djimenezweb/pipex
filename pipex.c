/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/06/24 14:28:43 by danielji         ###   ########.fr       */
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
	int		fd[2];
	int		prev_fd = -1;
	int		last_fd;
	int		i;
	pid_t	pids[argc - 3];

	i = 0;
	loops = argc - 3;
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
	{
		// Manage errors
	}
	last_fd = open(argv[4], O_RDWR|O_CREAT, 0666);
	if (last_fd == -1)
	{
		// Manage errors
	}

	while (i < loops)
	{
		char	*command;
		char	*fullcommand;
		char	**args;

		if (pipe(fd) == -1)
			return (1);
	
		pids[i] = fork();
		if (pids[i] < 0)
			return 2;
		if (pids[i] == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			command = split_command(argv[i + 2]);
			fullcommand = path(command, envp);
			args = ft_split(argv[i + 2], ' ');
			//args = split_args(argv[i + 2]);
			execve(fullcommand, args, NULL);
			free(command);
			free(fullcommand);
			free_arr_str(args);
		}
	}

	if (prev_fd != -1)
		close(prev_fd);
	if(i < loops - 1)
	{
		close(fd[1]);
		prev_fd = fd[0];
	}
	i = 0;
	while(i < loops)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}


/*		dup2(fd[0], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO); */
	close(last_fd);

	return (0);
}
