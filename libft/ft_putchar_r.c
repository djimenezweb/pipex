/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:18:29 by danielji          #+#    #+#             */
/*   Updated: 2025/05/19 16:20:11 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the character `c` and returns number of characters written */
ssize_t	ft_putchar_r(char c)
{
	ssize_t	written;

	written = write(1, &c, 1);
	return (written);
}
