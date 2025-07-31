/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_arr_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:44:09 by danielji          #+#    #+#             */
/*   Updated: 2025/07/31 11:46:32 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Frees each string in an array of strings up to the limit specified in `i`.
Frees the array itself. */
void	free_arr_str_l(char **arr, int i)
{
	if (!arr || i <= 0)
		return ;
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
}

/* Frees each string in an array of strings and the array itself. */
void	free_arr_str(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/* Frees each string in an array of strings up to the limit specified in `i`.
Frees the array itself. Exits program. */
void	free_arr_arr_str_exit_l(char ***arr, int i)
{
	while (i > 0)
		free_arr_str(arr[--i]);
	free(arr);
	exit(EXIT_FAILURE);
}

/* Frees array of array of strings */
void	free_arr_arr_str(char ***arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free_arr_str(arr[i]);
		i++;
	}
	free(arr);
}
