/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:58:43 by danielji          #+#    #+#             */
/*   Updated: 2025/06/25 11:28:59 by danielji         ###   ########.fr       */
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

// path.c
char	*path_env(char *envp[]);
char	*path(char *command, char *envp[]);

// pipex_helpers.c
void	wait_chidren(int count);
int		open_input(char *path);
int		open_output(char *path);
void	free_arr_str(char **arr);

// split_helpers.c
char	*split_command(char *str);
char	*split_args(char *str);

#endif