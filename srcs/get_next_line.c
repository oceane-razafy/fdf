/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:25:06 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/01 22:07:06 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*get_next_line(int fd, int restart)
{
	static char	*result;
	ssize_t		nb;
	char		buf[BUFFER_SIZE + 1];

	if (result == 0)
		result = ft_strndup("\0", 0);
	if ((restart == 1) || (restart == -1))
	{
		if (result != NULL)
		{
			free(result);
			result = NULL;
		}
		if (restart == 1)
			result = ft_strndup("\0", 0);
		else
			return (NULL);
	}
	if (result == NULL)
		return (ft_strndup("Error", 5));
	nb = read(fd, buf, BUFFER_SIZE);
	return (ft_line_loop(nb, &result, buf, fd));
}

char	*ft_line_loop(int nb, char **result, char *buf, int fd)
{
	while (nb >= 0)
	{
		buf[nb] = 0;
		*result = ft_strjoin(*result, buf);
		if (*result == NULL)
			return (ft_strndup("Error", 5));
		if (nb == 0 && (*result)[0] == 0)
			break ;
		if (ft_strchr(*result, '\n') == 1)
			return (ft_get_line(result));
		if (nb == 0)
			return (ft_last_line(result));
		nb = read(fd, buf, BUFFER_SIZE);
	}
	ft_free(result);
	return (NULL);
}

void	ft_free(char **result)
{
	if (*result != NULL)
	{
		free(*result);
		*result = NULL;
	}
}

char	*ft_get_line(char **result)
{
	char		*line;
	char		*str;
	char		*reminder;
	ssize_t		i;

	str = ft_strndup(*result, ft_strlen(*result));
	if (str == NULL)
		return (ft_strndup("Error", 5));
	ft_free(result);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_strndup(str, i + 1);
	if (line == NULL)
		return (ft_strndup("Error", 5));
	reminder = ft_strndup(str + i + 1, ft_strlen(str + i + 1));
	if (reminder == NULL)
		return (ft_strndup("Error", 5));
	free(str);
	*result = reminder;
	return (line);
}

char	*ft_last_line(char **result)
{
	char	*line;

	line = ft_strndup(*result, ft_strlen(*result));
	if (line == NULL)
		return (ft_strndup("Error", 5));
	ft_free(result);
	return (line);
}
