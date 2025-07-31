/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init_context.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:51:14 by danielji          #+#    #+#             */
/*   Updated: 2025/07/30 09:54:18 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Opens file in read-only and returns its fd.
On error prints a warning but still returns the fd. */
int	open_infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		printerror(ENOENT, path);
	return (fd);
}

/* Opens file for writing and returns its fd. Exits program on error. */
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

/* Returns an array with arrays of strings
representing the commands and arguments */
char	***get_cmd_args(int count, char *argv[])
{
	int		i;
	char	***arr;

	i = 0;
	arr = (char ***)malloc(sizeof(char **) * (count + 1));
	if (!arr)
		exit(EXIT_FAILURE);
	while (i < count)
	{
		arr[i] = ft_split(argv[i + 2], ' ');
		if (!arr[i])
		{
			while (i > 0)
			{
				i--;
				free_arr_str(arr[i]);
			}
			free(arr);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

/* Initializes and returns a `t_pipex` context */
t_pipex	init_context(int argc, char *argv[], char *envp[])
{
	t_pipex	ctx;

	ctx.loops = argc - 3;
	ctx.outfile_fd = open_outfile(argv[argc - 1]);
	ctx.infile_fd = open_infile(argv[1]);
	ctx.prev_fd = ctx.infile_fd;
	ctx.pids = (pid_t *)malloc(sizeof(pid_t) * ctx.loops);
	if (!ctx.pids)
		exit(EXIT_FAILURE);
	ctx.envp = envp;
	ctx.args = get_cmd_args(ctx.loops, argv);
	ctx.exec_paths = get_exec_paths(ctx.loops, ctx.args, envp);
	return (ctx);
}
