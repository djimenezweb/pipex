/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/06/17 11:52:24 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
		return (0);
	
	char *file1 = argv[1];
	int fd1 = open(file1, O_RDONLY);
	char **command1 = ft_split(argv[2], ' ');
	ft_printf("command1[0]: %s\n", command1[0]);
	ft_printf("command1[1]: %s\n", command1[1]);
	//char *command2 = argv[3];
	//char *file2 = argv[4];

	char *pathname = ft_strjoin("/usr/bin/", command1[0]);
	execve(pathname, command1, envp);
	free(command1);
	free(pathname);
	return (0);
}
