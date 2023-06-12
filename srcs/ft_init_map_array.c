/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:24:09 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/02 23:10:45 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	**ft_init_map(char **argv, int y_size, int *x_sizes)
{
	int		**map;
	int		i;
	int		fd;
	char	*line;

	map = (int **)malloc(sizeof(int *) * y_size);
	if (map == NULL)
		ft_map_error(map, NULL, 0, x_sizes);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_map_error(map, NULL, 0, x_sizes);
	i = 0;
	while (i < y_size)
	{
		line = ft_init_current_line(map, fd, x_sizes, i);
		ft_fill_map_line(map, x_sizes, line, i);
		free(line);
		line = NULL;
		i++;
	}
	get_next_line(-1, -1);
	return (map);
}

char	*ft_init_current_line(int **map, int fd, int *x_sizes, int i)
{
	char	*line;

	if (i == 0)
		line = get_next_line(fd, 1);
	else
		line = get_next_line(fd, 0);
	if (ft_strcmp(line, "Error") == 0)
		ft_map_error(map, line, i, x_sizes);
	x_sizes[i] = ft_compute_current_x_size(line);
	if (x_sizes[i] == -1)
	{
		line = NULL;
		ft_map_error(map, line, i, x_sizes);
	}		
	map[i] = (int *)malloc(sizeof(int) * x_sizes[i]);
	if (map[i] == NULL)
		ft_map_error(map, NULL, i, x_sizes);
	return (line);
}

void	ft_fill_map_line(int **map, int *x_sizes, char *line, int i)
{
	int	j;
	int	k;
	int	num_len;

	j = 0;
	k = 0;
	while (j < x_sizes[i])
	{
		num_len = 0;
		map[i][j] = ft_atoi(&line[k], &num_len);
		k = k + num_len;
		while (line[k] == ' ')
			k++;
		j++;
	}
}

int	ft_atoi(char *str, int *num_len)
{
	long	sign;
	long	nb;
	int		i;

	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
		(*num_len)++;
	}
	i = 1;
	nb = str[0] % '0';
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] % '0');
		i++;
	}
	*num_len = *num_len + i;
	return (sign * nb);
}
