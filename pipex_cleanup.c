/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 17:07:23 by danielji          #+#    #+#             */
/*   Updated: 2025/07/26 17:09:22 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* - Waits for children
- Frees allocated memory
- Closes open file descriptors */
void	pipex_cleanup(t_pipex ctx)
{
	wait_chidren(ctx.loops);
	free_arr_str(ctx.paths);
	//close(ctx.pipefd[0]);
	close(ctx.outfile_fd);
}
