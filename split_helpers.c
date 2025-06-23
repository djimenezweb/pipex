/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:52:20 by danielji          #+#    #+#             */
/*   Updated: 2025/06/23 13:15:23 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

char	*split_command(char *str)
{
	int		i;
	int		start;
	int		len;
	char	*command;

	i = 0;
	len = 0;
	while (str[i] && str[i] == ' ')
		i++;
	start = i;
	while (str[i] && str[i] != ' ')
	{
		i++;
		len++;
	}
	command = ft_substr(str, start, len);
	return (command);
}

char	*split_args(char *str)
{
	int		start;
	int		end;
	char	*args;

	start = 0;
	while (str[start] && str[start] == ' ')
		start++;
	while (str[start] && str[start] != ' ')
		start++;
	while (str[start] && str[start] == ' ')
		start++;
	end = ft_strlen(str) - 1;
	while (str[end] && str[end] == ' ')
		end--;
	args = ft_substr(str, start, (end - start + 1));
	return (args);
}
