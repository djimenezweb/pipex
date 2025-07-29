/* ONLY FOR DEBUG PURPOSES */

#include "pipex.h"

void	print_array_of_strings(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

void	print_array_of_array_of_strings(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			ft_printf("%s", arr[i][j]);
			if (arr[i][j + 1])
				ft_printf(", ");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
