/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:32:16 by danielji          #+#    #+#             */
/*   Updated: 2025/06/20 11:47:28 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"
/* PRUEBAS:
< Makefile grep libft | grep clean > outfile
grep libft < Makefile | grep clean > outfile

< Makefile grep libft | tr -d "@" > outfile
grep libft < Makefile | tr -d "@" > outfile
*/
int	main(int argc, char *argv[])
{
	if (argc != 5)
		return (0);

	int filedes[2];
	char **command1;
	char **command2;

	filedes[0] = open(argv[1], O_RDONLY);
	filedes[1] = open(argv[4], O_RDWR);

	pipe(filedes);
	command1 = ft_split(argv[2], ' ');
	command2 = ft_split(argv[3], ' ');

	//char *pathname = ft_strjoin("/usr/bin/", command1[0]);
	//execve(pathname, command1, envp);
	//free(command1);
	//free(pathname);
	return (0);
}
