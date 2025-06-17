/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:19:31 by danielji          #+#    #+#             */
/*   Updated: 2025/04/20 17:13:09 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the string `s` to the specified file descriptor. */
void	ft_putstr_fd(char *s, int fd)
{
	char	c;

	while (*s)
	{
		c = *s;
		write(fd, &c, 1);
		s++;
	}
}
