/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:32:35 by danielji          #+#    #+#             */
/*   Updated: 2025/07/30 11:44:27 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*trim(const char *s, char c)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	start = 0;
	end = ft_strlen(s);
	if (end == 0)
		return (ft_strdup(""));
	end--;
	while (s[start] == c)
		start++;
	while (s[end] == c)
		end--;
	if (start > end)
		return (ft_strdup(""));
	trimmed = ft_substr(s, start, (end - start + 1));
	return (trimmed);
}

static size_t	get_string_count(char const *s, char c)
{
	size_t	i;
	size_t	count;
	int		quote;

	i = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			i++;
			count++;
		}
		if (s[i] == '\'' && quote == 0)
			quote = 1;
		while ((s[i] && s[i] != c) || quote == 1)
		{
			i++;
			if (s[i] == '\'' && quote == 1)
				quote = 0;
		}
	}
	return (count);
}

static void	**string_to_array(char **arr, char const *str, char c, size_t count)
{
	size_t	i;
	size_t	start;
	size_t	end;
	int		inside_quote;

	i = 0;
	start = 0;
	end = 0;
	inside_quote = 0;
	while (count--)
	{
		while (str[start] == c)
			start++;
		end = start + 1;
		while (str[end])
		{
			if (str[end] == '\'' && (end == 0 || str[end - 1] != '\\'))
				inside_quote = !inside_quote;
			else if (str[end] == c && !inside_quote)
				break ;
			end++;
		}
		arr[i] = ft_substr(str, start, (end - start));
		if (!arr[i])
		{
			free_arr_str_l(arr, i);
			return (NULL);
		}
		start = end;
		i++;
	}
	arr[i] = (NULL);
	return (NULL);
}

/* Allocates memory and returns an array of strings obtained by splitting `s`
using the character `c` as a delimiter, skipping characters between single
quotes `'...'` */
char	**ft_split_quote(char const *s, char c)
{
	char	*str;
	char	**arr;
	size_t	count;

	if (!s)
		return (NULL);
	str = trim(s, c);
	if (!str)
		return (NULL);
	count = get_string_count(str, c);
	ft_printf("%s: contains %i strings\n", s, count);
	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
	{
		free(str);
		return (NULL);
	}
	string_to_array(arr, str, c, count);
	free(str);
	return (arr);
}
