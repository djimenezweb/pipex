/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:19:41 by danielji          #+#    #+#             */
/*   Updated: 2025/07/23 10:07:31 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Returns the first valid path to an executable file.
- Returns the provided string if it's already a valid path.
- Adds a `/` prefix only if it's missing.
- TO DO: Should check `.sh` files??? */
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
