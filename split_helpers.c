/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:52:20 by danielji          #+#    #+#             */
/*   Updated: 2025/06/23 23:26:00 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

static int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

char	*split_command(char *str)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	len = 0;
	while (str[i] && is_space(str[i]))
		i++;
	start = i;
	while (str[i] && !is_space(str[i]))
	{
		i++;
		len++;
	}
	return (ft_substr(str, start, len));
}

char	*split_args(char *str)
{
	int		start;
	int		end;

	start = 0;
	while (str[start] && is_space(str[start]))
		start++;
	while (str[start] && !is_space(str[start]))
		start++;
	while (str[start] && is_space(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (str[end] && is_space(str[end]))
		end--;
	return (ft_substr(str, start, (end - start + 1)));
}
