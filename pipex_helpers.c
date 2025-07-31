/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:23:32 by danielji          #+#    #+#             */
/*   Updated: 2025/07/30 10:15:26 by danielji         ###   ########.fr       */
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

/* Frees all allocated memory in `ctx` structure
Calls `exit(127)` if passed `exit_flag` */
void	free_context(t_pipex ctx, int exit_flag)
{
	if (ctx.pids)
		free(ctx.pids);
	if (ctx.args)
		free_arr_arr_str(ctx.args);
	if (ctx.exec_paths)
		free_arr_str(ctx.exec_paths);
	if (exit_flag > 0)
		exit(127);
}
