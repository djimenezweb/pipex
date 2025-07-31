/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:23:32 by danielji          #+#    #+#             */
/*   Updated: 2025/07/31 11:46:32 by danielji         ###   ########.fr       */
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
