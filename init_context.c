/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:51:14 by danielji          #+#    #+#             */
/*   Updated: 2025/07/23 12:18:38 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

/* Iterates through `envp` and returns the PATH string
(without the "PATH=" prefix)*/
char	*get_path_env(char *envp[])
{
	char	*path;

	while (*envp)
	{
		path = ft_strnstr(*envp, "PATH=", 5);
		if (path)
			return (path + 5);
		envp++;
	}
	return (NULL);
}

/* Opens the specified file in read-only mode
and returns its file descriptor. */
int	open_infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("pipex: no such file or directory: %s", path);
	}
	return (fd);
}

/* Opens the file at the given path for writing.
Creates the file if it doesn't exist and erases content if it does.
Returns the file descriptor. */
int	open_outfile(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		// Manage errors
	}
	return (fd);
}

/* Initializes a `t_pipex` context and returns it.
- `loops`: Number of commands.
- `prev_fd`: File descriptor from the previous file
(on first iteration, file descriptor for the input file).
- `outfile_fd`: File descriptor for the output file.
- `paths`: An array of directories to look for executable files.*/
t_pipex	init_context(int argc, char *argv[], char *envp[])
{
	t_pipex	ctx;

	ctx.loops = argc - 3;
	ctx.prev_fd = open_infile(argv[1]);
	ctx.outfile_fd = open_outfile(argv[argc - 1]);
	ctx.paths = ft_split(get_path_env(envp), ':');
	return (ctx);
}
