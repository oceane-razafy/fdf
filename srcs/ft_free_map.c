/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:16:09 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/01 21:28:44 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_map_array(int **map, int y_size)
{
	int	j;

	j = 0;
	while (j < y_size)
	{
		free(map[j]);
		j++;
	}
	free(map);
	map = NULL;
}

void	ft_free_map_struct(t_fdf *s_fdf)
{
	int	i;

	i = 0;
	while (i < s_fdf->nb_map_points_malloced)
	{
		free(s_fdf->map[i]);
		i++;
	}
	free(s_fdf->map);
}
