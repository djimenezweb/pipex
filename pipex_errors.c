/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:01:12 by danielji          #+#    #+#             */
/*   Updated: 2025/07/29 12:57:32 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

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
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errnum), STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

/* Outputs to `STDOUT` an error message that describes the error code
passed in the argument `errnum` and an optional string `str`. */
void	printwarn(int errnum, char *str)
{
	ft_putstr_fd("pipex: ", STDOUT_FILENO);
	ft_putstr_fd(strerror(errnum), STDOUT_FILENO);
	if (str)
	{
		ft_putstr_fd(": ", STDOUT_FILENO);
		ft_putstr_fd(str, STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}
