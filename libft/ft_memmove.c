/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:32:26 by danielji          #+#    #+#             */
/*   Updated: 2025/04/21 16:10:12 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies `n` bytes from memory area `src` to memory area `dest`.
The memory areas may overlap: copying takes place as though the bytes in
`src` are first copied into a temporary array that does not overlap `src` or
`dest`, and the bytes are then copied from the temporary array to `dest`.
Returns a pointer to `dest`. */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (dest < src && n != 0)
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	if (dest > src && n != 0)
	{
		d += n;
		s += n;
		while (n--)
		{
			*--d = *--s;
		}
	}
	return (dest);
}
