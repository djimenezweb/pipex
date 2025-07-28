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

/* Iterates through `envp` and returns the PATH string */
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

/* Opens file in read-only and returns its fd.
On error prints a warning but still returns the fd. */
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

/* Opens file for writing and returns its fd. Exits program on error */
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

/* Initializes and returns a `t_pipex` context */
t_pipex	init_context(int argc, char *argv[], char *envp[])
{
	t_pipex	ctx;
	char	*path;

	path = get_path_env(envp);
	ctx.loops = argc - 3;
	ctx.outfile_fd = open_outfile(argv[argc - 1]);
	ctx.infile_fd = open_infile(argv[1]);
	ctx.prev_fd = ctx.infile_fd;
	if (path)
		ctx.paths = ft_split(path, ':');
	else
		ctx.paths = NULL;
	ctx.argv = argv;
	ctx.envp = envp;
	return (ctx);
}
