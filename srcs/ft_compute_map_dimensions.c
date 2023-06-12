/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute_map_dimensions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:23:59 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/02 23:04:15 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_free_line(char *line)
{
	free(line);
	return (-1);
}

void	ft_skip_spaces(int *i, char *line)
{
	while (line[*i] == ' ')
		(*i)++;
}

int	ft_compute_current_x_size(char *line)
{
	int	i;
	int	x_size;

	i = 0;
	x_size = 0;
	while (line[i] != '\n')
	{
		if (i == 0 && line[i] == ' ')
			ft_skip_spaces(&i, line);
		if ((line[i] < '0' || line[i] > '9') && (line [i] != '+')
			&& (line[i] != '-'))
			return (ft_free_line(line));
		if ((line[i] == '+') || (line[i] == '-'))
			i++;
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		x_size++;
		while (line[i] == ' ')
			i++;
		if (line[i] == 0)
			return (x_size);
	}
	if ((i == 0) && (line[i] == '\n'))
		return (ft_free_line(line));
	return (x_size);
}

char	*ft_retrieve_line(int fd, int *y_size)
{
	char	*line;

	line = get_next_line(fd, 0);
	if (ft_strcmp(line, "Error") == 0)
	{
		ft_map_error(NULL, line, 0, NULL);
		free(line);
		exit(1);
	}
	if (line != NULL)
	{
		free(line);
		(*y_size)++;
	}
	return (line);
}

int	ft_compute_y_size(char **argv)
{
	int		y_size;
	char	*line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit (1);
	y_size = 0;
	line = ft_retrieve_line(fd, &y_size);
	while (line)
		line = ft_retrieve_line(fd, &y_size);
	close(fd);
	return (y_size);
}
