/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_create_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:05:34 by danielji          #+#    #+#             */
/*   Updated: 2025/07/26 17:08:27 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Creates a pipe except on last iteration */
void	create_pipe(int i, t_pipex *ctx)
{
	if (is_last(i, ctx->loops))
		return ;
	if (pipe(ctx->pipefd) == -1)
	{
		// Handle error;
	}
}
