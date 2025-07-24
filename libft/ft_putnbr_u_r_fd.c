/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u_r_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:23:33 by danielji          #+#    #+#             */
/*   Updated: 2025/07/24 17:21:44 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the unsigned integer `n` and
returns number of characters written */
ssize_t	ft_putnbr_u_r_fd(int fd, unsigned int n)
{
	char	c;
	ssize_t	written;

	written = 0;
	if (n / 10 > 0)
	{
		written += ft_putnbr_u_r_fd(fd, n / 10);
	}
	c = (n % 10) + '0';
	written += write(fd, &c, 1);
	return (written);
}
