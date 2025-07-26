/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:01:12 by danielji          #+#    #+#             */
/*   Updated: 2025/07/26 16:41:42 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

/* Outputs to STDERR an error message that describes the error code
passed in the argument `errnum` and an optional string `str`. */
void	printerror(int errnum, char *str)
{
	if (!str)
		ft_printf_fd(STDERR_FILENO, "pipex: %s\n", strerror(errnum));
	else
		ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n", strerror(errnum), str);
}

/* Outputs to STDOUT an error message that describes the error code
passed in the argument `errnum` and an optional string `str`. */
void	printwarn(int errnum, char *str)
{
	if (!str)
		ft_printf_fd(STDOUT_FILENO, "pipex: %s\n", strerror(errnum));
	else
		ft_printf_fd(STDOUT_FILENO, "pipex: %s: %s\n", strerror(errnum), str);
}
