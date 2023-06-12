/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:05:35 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/02 23:05:36 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_map_error(int **map, char *line, int i, int *x_sizes)
{
	int	j;

	j = 0;
	if (x_sizes != NULL)
		free(x_sizes);
	get_next_line(-1, -1);
	if (map == NULL)
	{
		if (line != NULL)
			free(line);
		exit(1);
	}
	if (line != NULL)
		free(line);
	while (j < i)
	{
		free(map[j]);
		j++;
	}
	free(map);
	exit (1);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if ((str1 == NULL) || (str2 == NULL))
		return (-1);
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (str1[i] == 0 && str2[i] == 0)
		return (0);
	return (-1);
}

void	ft_fdf_error(int **map, int y_size, t_fdf *s_fdf, int *x_sizes)
{
	if (s_fdf != NULL)
		s_fdf->is_error = 1;
	if (map != NULL)
		ft_free_map_array(map, y_size);
	if (x_sizes != NULL)
		free(x_sizes);
	if (s_fdf != NULL)
		s_fdf->x_sizes = NULL;
	close_window(s_fdf);
}
