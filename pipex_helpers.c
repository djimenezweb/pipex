/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:23:32 by danielji          #+#    #+#             */
/*   Updated: 2025/07/22 14:54:20 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Returns `1` if the current loop is the last one. Returns `0` otherwise. */
int	is_last(int i, int count)
{
	if (i == count - 1)
		return (1);
	return (0);
}

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
