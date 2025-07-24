/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_r_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:23:30 by danielji          #+#    #+#             */
/*   Updated: 2025/07/24 17:26:08 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the integer `n` and returns number of characters written */
ssize_t	ft_putnbr_r_fd(int fd, int n)
{
	char	c;
	ssize_t	written;

	written = 0;
	if (n == -2147483648)
	{
		written += write(fd, "-2147483648", 11);
		return (written);
	}
	if (n < 0)
	{
		written += write(fd, "-", 1);
		n = n * (-1);
	}
	if (n / 10 > 0)
	{
		written += ft_putnbr_r_fd(fd, n / 10);
	}
	c = (n % 10) + '0';
	written += write(fd, &c, 1);
	return (written);
}
