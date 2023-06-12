/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:24:54 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/01 22:06:28 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strjoin(char *str1, char *str2)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	len1;
	char	*dest;

	len1 = ft_strlen(str1);
	dest = (char *)malloc(sizeof(char) * (len1 + ft_strlen(str2) + 1));
	if (dest == NULL)
	{
		ft_free(&str1);
		return (NULL);
	}
	i = 0;
	while (str1[i])
	{
		dest[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
		dest[i++] = str2[j++];
	dest[i] = 0;
	ft_free(&str1);
	return (dest);
}

ssize_t	ft_strchr(char *str, char c)
{
	ssize_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strndup(char *str, ssize_t n)
{
	char		*dest;
	ssize_t		i;

	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
	{
		ft_free(&str);
		return (NULL);
	}
	i = 0;
	if (str != NULL)
	{
		while (str[i] && i < n)
		{
			dest[i] = str[i];
			i++;
		}
	}
	dest[i] = 0;
	return (dest);
}

ssize_t	ft_strlen(char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
