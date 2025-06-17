/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:23:30 by danielji          #+#    #+#             */
/*   Updated: 2025/05/19 16:24:59 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the integer `n` and returns number of characters written */
ssize_t	ft_putnbr_r(int n)
{
	char	c;
	ssize_t	written;

	written = 0;
	if (n == -2147483648)
	{
		written += write(1, "-2147483648", 11);
		return (written);
	}
	if (n < 0)
	{
		written += write(1, "-", 1);
		n = n * (-1);
	}
	if (n / 10 > 0)
	{
		written += ft_putnbr_r(n / 10);
	}
	c = (n % 10) + '0';
	written += write(1, &c, 1);
	return (written);
}
