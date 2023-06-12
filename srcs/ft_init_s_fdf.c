/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_s_fdf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:30:27 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/02 23:20:33 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*ft_init_s_fdf(int **map, int y_size, int *x_sizes)
{
	t_fdf	*s_fdf;

	s_fdf = NULL;
	s_fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (s_fdf == NULL)
		ft_fdf_error(map, y_size, s_fdf, x_sizes);
	s_fdf->is_error = 0;
	s_fdf->x_sizes = x_sizes;
	s_fdf->y_size = y_size;
	s_fdf->z_range = ft_get_z_range(map, s_fdf);
	s_fdf->map = ft_convert_map_array_to_struct(map, s_fdf);
	ft_free_map_array(map, s_fdf->y_size);
	s_fdf->mlx_ptr = mlx_init();
	if (s_fdf->mlx_ptr == NULL)
		ft_fdf_error(NULL, 0, s_fdf, x_sizes);
	s_fdf->mlx_win = mlx_new_window(s_fdf->mlx_ptr, W_WIDTH, W_HEIGHT, "FDF");
	if (s_fdf->mlx_win == NULL)
		ft_fdf_error(NULL, 0, s_fdf, x_sizes);
	return (s_fdf);
}

t_point	**ft_convert_map_array_to_struct(int **map, t_fdf *s_fdf)
{
	int	y;
	int	x;

	s_fdf->map = (t_point **)malloc(sizeof(t_point *) * s_fdf->y_size);
	if (s_fdf->map == NULL)
		ft_fdf_error(map, s_fdf->y_size, s_fdf, NULL);
	s_fdf->nb_map_points_malloced = 0;
	y = 0;
	while (y < s_fdf->y_size)
	{
		s_fdf->map[y] = (t_point *)malloc(sizeof(t_point) * s_fdf->x_sizes[y]);
		if (s_fdf->map[y] == NULL)
			ft_fdf_error(map, s_fdf->y_size, s_fdf, NULL);
		s_fdf->nb_map_points_malloced++;
		x = 0;
		while (x < s_fdf->x_sizes[y])
		{
			s_fdf->map[y][x].y = y;
			s_fdf->map[y][x].x = x;
			s_fdf->map[y][x].z = map[y][x];
			x++;
		}
		y++;
	}
	return (s_fdf->map);
}

int	ft_get_z_range(int **map, t_fdf *s_fdf)
{
	int	max;
	int	min;
	int	y;
	int	x;

	max = map[0][0];
	min = map[0][0];
	y = 0;
	while (y < s_fdf->y_size)
	{
		x = 0;
		while (x < s_fdf->x_sizes[y])
		{
			if (map[y][x] > max)
				max = map[y][x];
			if (min > map[y][x])
				min = map[y][x];
			x++;
		}
		y++;
	}
	s_fdf->z_max = max;
	s_fdf->z_min = min;
	return (abs(max - min));
}
