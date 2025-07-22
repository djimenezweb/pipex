/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:19:41 by danielji          #+#    #+#             */
/*   Updated: 2025/07/22 14:21:09 by danielji         ###   ########.fr       */
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

/* Returns the first valid path to an executable file.
Checks whether the provided string is already a valid path.
TO DO: Should check `.sh` files. */
char	*path(char *str, char **paths)
{
	int		i;
	char	*command;
	char	*pathname;

	if (access(str, X_OK) == 0)
		return (str);
	i = 0;
	command = ft_strjoin("/", str);
	while (paths[i])
	{
		pathname = ft_strjoin(paths[i], command);
		if (access(pathname, X_OK) == 0)
			break ;
		free(pathname);
		i++;
	}
	free(command);
	return (pathname);
}
