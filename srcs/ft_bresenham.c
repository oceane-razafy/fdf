/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:34:57 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/04 18:32:58 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_bresenham(t_fdf *s_fdf, t_point point_1, t_point point_2)
{
	while (1)
	{
		if (point_1.x < 0 || point_1.y < 0
			|| point_1.x > W_WIDTH || point_1.y > W_HEIGHT)
			break ;
		ft_put_pixel(s_fdf, point_1);
		if ((point_1.x == point_2.x) && (point_1.y == point_2.y))
			break ;
		s_fdf->bresen.error2 = 2 * s_fdf->bresen.error;
		if (s_fdf->bresen.error2 >= -(s_fdf->bresen.dy))
		{
			if (point_1.x == point_2.x)
				break ;
			s_fdf->bresen.error -= s_fdf->bresen.dy;
			point_1.x += s_fdf->bresen.incx;
		}
		if (s_fdf->bresen.error2 <= s_fdf->bresen.dx)
		{
			if (point_1.y == point_2.y)
				break ;
			s_fdf->bresen.error += s_fdf->bresen.dx;
			point_1.y += s_fdf->bresen.incy;
		}
	}
}

void	ft_create_line(t_fdf *s_fdf, t_point point_1, t_point point_2)
{
	ft_project_iso(&point_1, s_fdf);
	ft_project_iso(&point_2, s_fdf);
	ft_param_bresen(s_fdf, point_1, point_2);
	ft_bresenham(s_fdf, point_1, point_2);
}

void	ft_project_iso(t_point *p, t_fdf *s_fdf)
{
	int		scale;
	double	pi;
	int		x;
	int		y;
	int		z;

	x = p->x;
	y = p->y;
	z = p->z;
	pi = 3.14159265358979323846;
	scale = ft_compute_scale(s_fdf);
	x *= scale;
	y *= scale;
	z *= scale;
	p->x = (x - y) * cos(pi / 8);
	p->y = (x + y) * sin(pi / 8) - (z);
	p->x += W_WIDTH / 2;
	p->y += W_HEIGHT / 2;
}

int	ft_compute_scale(t_fdf *s_fdf)
{
	int	scale;
	int	possible_scale_1;
	int	possible_scale_2;
	int	max_map_dim;
	int	max_win_dim;

	ft_get_max_x_size(s_fdf);
	max_map_dim = fmax(s_fdf->max_x_size, s_fdf->y_size);
	max_win_dim = fmax(W_WIDTH, W_HEIGHT);
	possible_scale_1 = max_win_dim / (2.5 * max_map_dim);
	if (3 * s_fdf->z_range == 0)
		scale = possible_scale_1;
	else
	{
		possible_scale_2 = max_win_dim / (3 * s_fdf->z_range);
		scale = fmin(possible_scale_1, possible_scale_2);
	}
	if (scale == 0)
		return (1);
	return (scale);
}

void	ft_param_bresen(t_fdf *s_fdf, t_point point_1, t_point point_2)
{
	s_fdf->bresen.dx = abs(point_2.x - point_1.x);
	s_fdf->bresen.dy = abs(point_2.y - point_1.y);
	s_fdf->bresen.incx = ft_compute_incrementation(point_1.x, point_2.x);
	s_fdf->bresen.incy = ft_compute_incrementation(point_1.y, point_2.y);
	s_fdf->bresen.error = s_fdf->bresen.dx - s_fdf->bresen.dy;
	s_fdf->bresen.color = ft_get_color(point_1.z, point_2.z, s_fdf);
}
