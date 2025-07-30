/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:01:12 by danielji          #+#    #+#             */
/*   Updated: 2025/07/30 13:34:46 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Calls `perror()` and exits program. */
void	perror_and_exit(void)
{
	perror("pipex");
	exit(EXIT_FAILURE);
}

/* Outputs to `STDERR` `command not found: <cmd>`. */
void	print_cmd_not_found(char *cmd)
{
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
}

/* Outputs to `STDERR` an error message that describes the error code
passed in the argument `errnum` and an optional string `str`. */
void	printerror(int errnum, char *str)
{
	if (errnum > 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errnum), STDERR_FILENO);
		if (str)
			ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (!errnum || !str)
		ft_putstr_fd("Unknown error", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
