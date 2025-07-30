/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:43 by danielji          #+#    #+#             */
/*   Updated: 2025/07/30 13:35:01 by danielji         ###   ########.fr       */
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
# include <stdio.h>
# include <errno.h>

typedef struct s_pipex
{
	int		loops;
	int		outfile_fd;
	int		infile_fd;
	int		prev_fd;
	int		pipefd[2];
	pid_t	*pids;
	char	**envp;
	char	***args;
	char	**exec_paths;
}			t_pipex;

/* pipex.c AND pipex_bonus.c */

void	bad_args(void);

/* pipex_errors.c */

void	perror_and_exit(void);
void	print_cmd_not_found(char *cmd);
void	printerror(int errnum, char *str);

/* pipex_fork_process.c */

pid_t	fork_process(int i, t_pipex *ctx);

/* pipex_get_exec_paths.c */

char	*get_path_env(char *envp[]);
char	*get_command_path(char *cmd, char **paths);
char	**get_path_dirs(char *envp[]);
char	**get_exec_paths(int count, char ***args, char *envp[]);

/* pipex_helpers.c */

int		is_last(int i, int count);
void	free_arr_str(char **arr);
void	free_arr_str_l(char **arr, int i);
void	free_arr_arr_str(char ***arr);
void	free_context(t_pipex ctx, int exit_flag);

/* pipex_init_context.c */

int		open_infile(char *path);
int		open_outfile(char *path);
char	***get_cmd_args(int count, char *argv[]);
t_pipex	init_context(int argc, char *argv[], char *envp[]);

/* pipex_run_child.c */

void	redirect_stdio(int i, t_pipex ctx);
void	cleanup_child(int i, t_pipex ctx);
void	exec_child(int i, t_pipex ctx);

/* pipex_split_quote.c */
char	**ft_split_quote(char const *s, char c);

/* DEBUG ONLY - DO NOT INCLUDE !!!! */
void	print_array_of_strings(char **arr);
void	print_array_of_array_of_strings(char ***arr);

#endif