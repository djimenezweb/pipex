/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_r_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:18:29 by danielji          #+#    #+#             */
/*   Updated: 2025/07/24 17:17:24 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the character `c` and returns number of characters written */
ssize_t	ft_putchar_r_fd(int fd, char c)
{
	ssize_t	written;

	written = write(fd, &c, 1);
	return (written);
}
