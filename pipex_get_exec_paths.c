/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_exec_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:01:01 by danielji          #+#    #+#             */
/*   Updated: 2025/07/30 09:51:34 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Iterates through `envp` and returns `PATH` */
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

/* Adds a `/` to the beginning of a string `str` if it's missing. */
char	*add_slash(char *str)
{
	if (!str)
		return (ft_strdup(""));
	if (!ft_strnstr(str, "/", 1))
		return (ft_strjoin("/", str));
	return (ft_strdup(str));
}

/* Returns the first valid path to an executable file
or an empty string if not a valid command */
char	*get_command_path(char *cmd, char **paths)
{
	int		i;
	char	*pathname;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!cmd || !cmd[0] || !paths || !paths[0])
		return (ft_strdup(""));
	i = 0;
	cmd = add_slash(cmd);
	while (paths[i])
	{
		pathname = ft_strjoin(paths[i], cmd);
		if (access(pathname, X_OK) == 0)
		{
			free(cmd);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	free(cmd);
	return (ft_strdup(""));
}

/* Parses PATH variable from `envp` into an array of directory strings.
Returns an empty array if `PATH` or `environment` are missing. */
char	**get_path_dirs(char *envp[])
{
	char	*path;
	char	**paths;

	if (!envp)
		return (ft_split("", ':'));
	path = get_path_env(envp);
	if (!path)
		paths = ft_split("", ':');
	else
		paths = ft_split(path, ':');
	if (!paths)
		exit(EXIT_FAILURE);
	return (paths);
}

/* Returns array of executable paths for given commands.
 Returns empty array if envp is NULL or does not contain PATH variable. */
char	**get_exec_paths(int count, char ***args, char *envp[])
{
	int		i;
	char	**path_dirs;
	char	**exec_paths;

	i = 0;
	path_dirs = get_path_dirs(envp);
	exec_paths = malloc(sizeof(char *) * (count + 1));
	if (!exec_paths)
	{
		free_arr_str(path_dirs);
		exit(EXIT_FAILURE);
	}
	while (i < count)
	{
		exec_paths[i] = get_command_path(args[i][0], path_dirs);
		if (!exec_paths[i])
		{
			free_arr_str_l(exec_paths, i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	exec_paths[count] = NULL;
	free_arr_str(path_dirs);
	return (exec_paths);
}
