/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:19:41 by danielji          #+#    #+#             */
/*   Updated: 2025/06/24 11:55:22 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	free_arr_str(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*path_env(char *envp[])
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH", 4))
			return(ft_strnstr(*envp, "PATH", 4) + 5);
		envp++;
	}
	return (NULL);
}

char	*path(char *str, char *envp[])
{
	int		i;
	char	*command;
	char	*fullpath;
	char	**paths;

	if (access(str, X_OK) == 0)
		return (str);

	i = 0;
	command = ft_strjoin("/", str);
	paths = ft_split(path_env(envp), ':');
	while (paths[i])
	{
		fullpath = ft_strjoin(paths[i], command);
		if (access(fullpath, X_OK) == 0)
			break;
		free(fullpath);
		i++;
	}
	free(command);
	free_arr_str(paths);
	return (fullpath);
}
