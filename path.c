/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:19:41 by danielji          #+#    #+#             */
/*   Updated: 2025/06/25 13:17:11 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

char	*get_path_env(char *envp[])
{
	char	*path;

	while (*envp)
	{
		path = ft_strnstr(*envp, "PATH", 4);
		if (path)
			return (path + 5);
		envp++;
	}
	return (NULL);
}

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
