/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/06/22 21:01:01 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"
/* PRUEBAS:
< Makefile grep libft | grep clean > outfile

< Makefile grep libft | tr -d "@" > outfile
./pipex Makefile "grep libft" "tr -d @" outfile
*/
int	main(int argc, char *argv[])
{
	/* if (argc != 5)
		return (0); */
	(void)argc;
	(void)argv;
	int fd[2];
	pid_t	pid1;
	pid_t	pid2;
	/* char **command1;
	char **command2; */

	/* fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_RDWR); */

	if (pipe(fd) == -1)
		return (1);

	// CHILD PROCESS 1
	pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			char **args = ft_split("ping -c 3 google.com", ' ');
			execve("/usr/bin/ping", args, NULL);
			free(args);
	}

	// CHILD PROCESS 2
	pid2 = fork();
	if (pid2 < 0)
		return 3;
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		char **args = ft_split("grep rtt", ' ');
		execve("/usr/bin/grep", args, NULL);
		free(args);
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

/*	command1 = ft_split(argv[2], ' ');
	command2 = ft_split(argv[3], ' ');
	char *pathname1 = ft_strjoin("/usr/bin/", command1[0]);
	execve(pathname1, command1, envp);
	free(command1);
	free(pathname1);*/
	return (0);
}
