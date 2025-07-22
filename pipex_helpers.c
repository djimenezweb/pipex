/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:23:32 by danielji          #+#    #+#             */
/*   Updated: 2025/07/22 12:49:10 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

/* Waits for the specified number of child processes to finish. */
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

/* Opens the specified file in read-only mode
and returns its file descriptor. */
int	open_infile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		// Manage errors
	}
	return (fd);
}

/* Opens the file at the given path for writing.
Creates the file if it doesn't exist and erases content if it does.
Returns the file descriptor. */
int	open_outfile(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		// Manage errors
	}
	return (fd);
}

/* Frees each string in an array of strings and the array itself. */
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
