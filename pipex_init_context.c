/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_context.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:51:14 by danielji          #+#    #+#             */
/*   Updated: 2025/07/26 17:08:45 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
and returns its file descriptor.
On error it prints a warning but still returns the fd. */
int	open_infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printwarn(ENOENT, path);
	}
	return (fd);
}

/* Opens the file at the given path for writing.
Creates the file if it doesn't exist and erases content if it does.
Returns the file descriptor.
Exits program on error (access not allowed, not valid directory). */
int	open_outfile(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (!access(path, F_OK) && access(path, W_OK) < 0)
			printerror(EACCES, path);
		else
			printerror(ENOENT, path);
		exit(1);
	}
	return (fd);
}

/* char	**parse_commands(int count, char *argv[], char *paths[])
{
	int		i;
	char	**commands;

	commands = malloc(sizeof(char*) * (count + 1));
	if (!commands)
		return (NULL);
	i = 0;
	while(i < count)
	{
		commands[i] = get_command_path(argv[i + 2], paths);
		// handle malloc error
		i++;
	}
	commands[i] = NULL;
	return (commands);
} */

/* Initializes a `t_pipex` context and returns it.
- `loops`: Number of commands.
- `prev_fd`: File descriptor from the previous file
(on first iteration, file descriptor for the input file).
- `outfile_fd`: File descriptor for the output file.
- `paths`: An array of directories to look for executable files.
- `argv`: A reference to the original `argv`.
- `envp`: A reference to the original `envp`. */
t_pipex	init_context(int argc, char *argv[], char *envp[])
{
	t_pipex	ctx;

	ctx.loops = argc - 3;
	ctx.outfile_fd = open_outfile(argv[argc - 1]);
	ctx.infile_fd = open_infile(argv[1]);
	ctx.prev_fd = ctx.infile_fd;
	ctx.paths = ft_split(get_path_env(envp), ':');
	ctx.argv = argv;
	ctx.envp = envp;
	return (ctx);
}
