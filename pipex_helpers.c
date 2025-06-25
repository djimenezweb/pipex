/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:23:32 by danielji          #+#    #+#             */
/*   Updated: 2025/06/25 11:28:53 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	wait_chidren(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		wait(NULL);
		i++;
	}
}

int	open_input(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		// Manage errors
	}
	return (fd);
}

int	open_output(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		// Manage errors
	}
	return (fd);
}

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
