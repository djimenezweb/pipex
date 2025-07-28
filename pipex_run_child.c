/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:55:28 by danielji          #+#    #+#             */
/*   Updated: 2025/07/28 09:10:17 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

/* Redirects input from previous fd and output to pipeline's write end.
On last iteration, output is instead redirected to outfile */
static void	redirect_stdio(int i, t_pipex ctx)
{
	dup2(ctx.prev_fd, STDIN_FILENO);
	if (is_last(i, ctx.loops))
		dup2(ctx.outfile_fd, STDOUT_FILENO);
	else
		dup2(ctx.pipefd[1], STDOUT_FILENO);
}

/* Closes fds. On last iteration, closes outfile fd */
static void	cleanup_child(int i, t_pipex ctx)
{
	close(ctx.prev_fd);
	if (!is_last(i, ctx.loops))
	{
		close(ctx.pipefd[0]);
		close(ctx.pipefd[1]);
	}
	if (is_last(i, ctx.loops))
		close(ctx.outfile_fd);
}

/* Returns the first valid path to an executable file
or an empty string if not a valid command */
char	*get_command_path(char *cmd, char **paths)
{
	int		i;
	char	*slash_cmd;
	char	*pathname;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	if (!ft_strnstr(cmd, "/", 1))
		slash_cmd = ft_strjoin("/", cmd);
	else
		slash_cmd = ft_strdup(cmd);
	while (paths[i])
	{
		pathname = ft_strjoin(paths[i], slash_cmd);
		if (access(pathname, X_OK) == 0)
		{
			free(slash_cmd);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	free(slash_cmd);
	return (ft_strdup(""));
}

/* Sets up input/output redirection, closes fds, and runs the command. */
void	run_pipeline_child(int i, t_pipex ctx)
{
	char	*command;
	char	*pathname;
	char	**args;

	if (i == 0 && ctx.infile_fd < 0)
	{
		// handle invalid infile
		exit(127);
	}
	redirect_stdio(i, ctx);
	cleanup_child(i, ctx);
	command = split_command(ctx.argv[i + 2]);
	if (command[0] == '\0')
	{
		// handle empty command
		free(command);
		exit(127);
	}
	args = ft_split(ctx.argv[i + 2], ' ');
	pathname = get_command_path(command, ctx.paths);
	if (pathname[0] == '\0' || execve(pathname, args, ctx.envp) == -1)
	{
		free(command);
		free(pathname);
		free_arr_str(args);
		exit(127);
	}
}
