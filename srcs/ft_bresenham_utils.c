/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bresenham_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:38:59 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/04 18:32:46 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_get_max_x_size(t_fdf *s_fdf)
{
	int	y;	

	y = 0;
	s_fdf->max_x_size = s_fdf->x_sizes[y];
	while (y < s_fdf->y_size)
	{
		if (s_fdf->x_sizes[y] > s_fdf->max_x_size)
			s_fdf->max_x_size = s_fdf->x_sizes[y];
		y++;
	}
}

int	ft_get_color(double z1, double z2, t_fdf *s_fdf)
{
	double	pos1;
	double	pos2;

	pos1 = (z1 - s_fdf->z_min) / s_fdf->z_range;
	pos2 = (z2 - s_fdf->z_min) / s_fdf->z_range;
	if (pos1 >= 0.9 || pos2 >= 0.9)
		return (0x00FFFF);
	if (pos1 >= 0.8 || pos2 >= 0.8)
		return (0x00E5FF);
	if (pos1 >= 0.7 || pos2 >= 0.7)
		return (0x00CCFF);
	if (pos1 >= 0.6 || pos2 >= 0.6)
		return (0x00B2FF);
	if (pos1 >= 0.5 || pos2 >= 0.5)
		return (0x0099FF);
	if (pos1 >= 0.4 || pos2 >= 0.4)
		return (0x007FFF);
	if (pos1 >= 0.3 || pos2 >= 0.3)
		return (0x0066FF);
	if (pos1 >= 0.2 || pos2 >= 0.2)
		return (0x004CFF);
	if (pos1 >= 0.1 || pos2 >= 0.1)
		return (0x0033FF);
	return (0x0000FF);
}

int	ft_compute_incrementation(int v1, int v2)
{
	if (v1 < v2)
		return (1);
	return (-1);
}

void	ft_put_pixel(t_fdf *s_fdf, t_point p1)
{
	char	*addr_pixel;

	addr_pixel = s_fdf->image->data + p1.y * s_fdf->image->len;
	addr_pixel = addr_pixel + p1.x *(s_fdf->image->bpp / 8);
	*(int *)addr_pixel = s_fdf->bresen.color;
}
