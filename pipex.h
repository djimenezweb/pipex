/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:43 by danielji          #+#    #+#             */
/*   Updated: 2025/06/25 13:19:06 by danielji         ###   ########.fr       */
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
	int		output_fd;
	int		fd[2];
	char	**paths;
}			t_pipex;

// path.c
char	*get_path_env(char *envp[]);
char	*path(char *str, char **paths);

// pipex_helpers.c
void	wait_chidren(int count);
int		open_input(char *path);
int		open_output(char *path);
void	free_arr_str(char **arr);

// pipex.c
int		is_last(int i, int count);
void	run_command(char *str, t_pipex p, char *envp[]);
void	child_process(int i, t_pipex p, char *str, char *envp[]);

// split_helpers.c
char	*split_command(char *str);
char	*split_args(char *str);

#endif