/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:19:49 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/02 23:13:53 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	int		*x_sizes;
	int		y_size;
	int		**map;

	if (argc != 2)
		return (1);
	y_size = ft_compute_y_size(argv);
	if (y_size == 0)
		exit (1);
	x_sizes = (int *)malloc(sizeof(int) * y_size);
	if (x_sizes == NULL)
		exit (1);
	map = ft_init_map(argv, y_size, x_sizes);
	ft_fdf(map, y_size, x_sizes);
	return (0);
}

void	ft_fdf(int **map, int y_size, int *x_sizes)
{
	t_fdf	*s_fdf;
	t_image	img;

	s_fdf = ft_init_s_fdf(map, y_size, x_sizes);
	s_fdf->image = &img;
	s_fdf->image->ptr = NULL;
	img.ptr = mlx_new_image(s_fdf->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (img.ptr == NULL)
		ft_fdf_error(NULL, 0, s_fdf, x_sizes);
	img.data = (char *)mlx_get_data_addr(img.ptr, &img.bpp, &img.len, &img.end);
	if (img.data == NULL)
		ft_fdf_error(NULL, 0, s_fdf, x_sizes);
	ft_create_3d_wireframe(s_fdf);
	mlx_put_image_to_window(s_fdf->mlx_ptr, s_fdf->mlx_win, img.ptr, 0, 0);
	mlx_hook(s_fdf->mlx_win, 17, 0, &close_window, s_fdf);
	mlx_hook(s_fdf->mlx_win, 2, 1L << 0, &key_press, s_fdf);
	mlx_loop(s_fdf->mlx_ptr);
}

void	ft_create_3d_wireframe(t_fdf *s_fdf)
{
	int	y;
	int	x;

	y = 0;
	while (y < s_fdf->y_size)
	{
		x = 0;
		while (x < s_fdf->x_sizes[y])
		{
			if (x + 1 != s_fdf->x_sizes[y])
				ft_create_line(s_fdf, s_fdf->map[y][x], s_fdf->map[y][x + 1]);
			if ((y + 1 != s_fdf->y_size) && (x < s_fdf->x_sizes[y + 1]))
				ft_create_line(s_fdf, s_fdf->map[y][x], s_fdf->map[y + 1][x]);
			x++;
		}
		y++;
	}
}

int	key_press(int keycode, t_fdf *s_fdf)
{
	if (keycode == 65307)
		close_window(s_fdf);
	return (0);
}

int	close_window(t_fdf *s_fdf)
{
	int	is_error;

	is_error = 0;
	if (s_fdf == NULL)
		exit(1);
	if (s_fdf->is_error != 0)
		is_error = 1;
	if (s_fdf->x_sizes != NULL)
		free(s_fdf->x_sizes);
	if (s_fdf->mlx_ptr != NULL && s_fdf->image->ptr != NULL)
		mlx_destroy_image(s_fdf->mlx_ptr, s_fdf->image->ptr);
	if (s_fdf->mlx_ptr != NULL && s_fdf->mlx_win != NULL)
		mlx_destroy_window(s_fdf->mlx_ptr, s_fdf->mlx_win);
	if (s_fdf->mlx_ptr != NULL)
		mlx_destroy_display(s_fdf->mlx_ptr);
	if (s_fdf->map != NULL)
		ft_free_map_struct(s_fdf);
	if (s_fdf->mlx_ptr != NULL)
		free(s_fdf->mlx_ptr);
	free(s_fdf);
	if (is_error == 1)
		exit(1);
	exit(0);
}
