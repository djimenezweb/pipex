/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_r_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:19:31 by danielji          #+#    #+#             */
/*   Updated: 2025/07/24 17:19:24 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the string `s` and returns number of characters written.*/
ssize_t	ft_putstr_r_fd(int fd, char *s)
{
	ssize_t	written;

	written = 0;
	if (!s)
		written += write(fd, "(null)", 6);
	while (s && *s)
	{
		written += write(fd, s, 1);
		s++;
	}
	return (written);
}
