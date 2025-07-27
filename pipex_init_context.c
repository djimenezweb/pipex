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

/* Returns the first valid path to an executable file */
/* TO DO: Should return "" if not a valid command ????? */
char	*get_command_path(char *cmd, char **paths)
{
	int		i;
	char	*slash_cmd;
	char	*pathname;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	if (!ft_strnstr(cmd, "/", 1))
		slash_cmd = ft_strjoin("/", cmd);
	else
		slash_cmd = ft_strdup(cmd);
	while (paths[i])
	{
		pathname = ft_strjoin(paths[i], slash_cmd);
		if (access(pathname, X_OK) == 0)
			break ;
		free(pathname);
		i++;
	}
	free(slash_cmd);
	return (pathname);
}

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

	ctx.loops = argc - 3;
	ctx.outfile_fd = open_outfile(argv[argc - 1]);
	ctx.infile_fd = open_infile(argv[1]);
	ctx.prev_fd = ctx.infile_fd;
	ctx.paths = ft_split(get_path_env(envp), ':');
	ctx.argv = argv;
	ctx.envp = envp;
	return (ctx);
}
