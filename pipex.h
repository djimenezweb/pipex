/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:43 by danielji          #+#    #+#             */
/*   Updated: 2025/07/26 17:15:01 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

typedef struct s_pipex
{
	int		loops;
	int		infile_fd;
	int		outfile_fd;
	int		prev_fd;
	int		pipefd[2];
	char	**paths;
	char	**argv;
	char	**envp;
}			t_pipex;

char	*get_command_path(char *cmd, char **paths);
void	pipex_cleanup(t_pipex ctx);
void	create_pipe(int i, t_pipex *ctx);
void	printerror(int errnum, char *str);
void	printwarn(int errnum, char *str);
void	fork_process(int *i, t_pipex *ctx);
int		is_last(int i, int count);
void	wait_chidren(int count);
void	free_arr_str(char **arr);

char	*get_path_env(char *envp[]);
int		open_infile(char *path);
int		open_outfile(char *path);
t_pipex	init_context(int argc, char *argv[], char *envp[]);

void	run_pipeline_child(int i, t_pipex ctx);
char	*split_command(char *str);
char	*split_args(char *str);

#endif