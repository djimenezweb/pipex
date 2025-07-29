/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_exec_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:01:01 by danielji          #+#    #+#             */
/*   Updated: 2025/07/29 19:48:50 by danielji         ###   ########.fr       */
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

/* TO DO: TOO MANY LINES */
/* Returns the first valid path to an executable file
or an empty string if not a valid command */
char	*get_command_path(char *cmd, char **paths)
{
	int		i;
	char	*slash_cmd;
	char	*pathname;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!paths || !paths[0])
		return (ft_strdup(""));
	i = 0;
	if (!ft_strnstr(cmd, "/", 1))
		slash_cmd = ft_strjoin("/", cmd);
	else
		slash_cmd = ft_strdup(cmd);
	while (paths[i])
	{
		pathname = ft_strjoin(paths[i], slash_cmd);
		if (access(pathname, X_OK) == 0)
		{
			free(slash_cmd);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	free(slash_cmd);
	return (ft_strdup(""));
}

/* Parses PATH variable from `envp` into an array of directory strings.
Returns an empty array if PATH or `environment` are missing. */
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

/* TO DO: Free previously allocated memory */
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
		// Free previously allocated memory
		exit(EXIT_FAILURE);
	}
	while (i < count)
	{
		exec_paths[i] = get_command_path(args[i][0], path_dirs);
		i++;
	}
	exec_paths[count] = NULL;
	free_arr_str(path_dirs);
	return (exec_paths);
}
