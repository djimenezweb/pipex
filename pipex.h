/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:43 by danielji          #+#    #+#             */
/*   Updated: 2025/07/22 15:06:34 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		loops;
	int		prev_fd;
	int		outfile_fd;
	int		pipefd[2];
	char	**paths;
}			t_pipex;

// init_context.c
char	*get_path_env(char *envp[]);
int		open_infile(char *path);
int		open_outfile(char *path);
t_pipex	init_context(int argc, char *argv[], char *envp[]);

// paths.c
char	*path(char *str, char **paths);

// pipex_helpers.c
int		is_last(int i, int count);
void	wait_chidren(int count);
void	free_arr_str(char **arr);

// pipex.c
// int	main(int argc, char *argv[], char *envp[])

// run_child.c
void	run_command(char *str, t_pipex ctx, char *envp[]);
void	run_pipeline_child(int i, t_pipex ctx, char *str, char *envp[]);

// split_helpers.c
char	*split_command(char *str);
char	*split_args(char *str);

#endif