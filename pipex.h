/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:43 by danielji          #+#    #+#             */
/*   Updated: 2025/07/22 12:52:45 by danielji         ###   ########.fr       */
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

// paths.c
char	*get_path_env(char *envp[]);
char	*path(char *str, char **paths);

// pipex_helpers.c
void	wait_chidren(int count);
int		open_infile(char *path);
int		open_outfile(char *path);
void	free_arr_str(char **arr);

// pipex.c
int		is_last(int i, int count);
void	run_command(char *str, t_pipex ctx, char *envp[]);
void	child_process(int i, t_pipex ctx, char *str, char *envp[]);
t_pipex	init_context(int argc, char *argv[], char *envp[]);

// split_helpers.c
char	*split_command(char *str);
char	*split_args(char *str);

#endif