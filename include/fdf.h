/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:20:08 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/04 18:30:36 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "mlx.h"
# include <math.h>
# define BUFFER_SIZE 1042
# define W_WIDTH 1000
# define W_HEIGHT 1000

typedef struct s_point
{
	int	y;
	int	x;
	int	z;
}				t_point;

typedef struct s_image
{
	void	*ptr;
	char	*data;
	int		len;
	int		bpp;
	int		end;
}				t_image;

typedef struct s_bresen
{
	int	dx;
	int	dy;
	int	incx;
	int	incy;
	int	error;
	int	error2;
	int	color;
}				t_bresen;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_point		**map;
	t_image		*image;
	int			*x_sizes;
	int			max_x_size;
	int			y_size;
	int			color;
	long long	z_range;
	int			z_max;
	int			z_min;
	t_bresen	bresen;
	int			nb_map_points_malloced;
	int			is_error;
}				t_fdf;

// fdf.c
void		ft_fdf(int **map, int y_size, int *x_sizes);
void		ft_create_3d_wireframe(t_fdf *s_fdf);
int			key_press(int keycode, t_fdf *s_fdf);
int			close_window(t_fdf *s_fdf);

// ft_bresenham_utils.c
void		ft_get_max_x_size(t_fdf *s_fdf);
int			ft_get_color(double z1, double z2, t_fdf *s_fdf);
int			ft_compute_incrementation(int v1, int v2);
void		ft_put_pixel(t_fdf *s_fdf, t_point p1);

// ft_bresenham.c
void		ft_bresenham(t_fdf *s_fdf, t_point point_1, t_point point_2);
void		ft_create_line(t_fdf *s_fdf, t_point point_1, t_point point_2);
void		ft_project_iso(t_point *p, t_fdf *s_fdf);
int			ft_compute_scale(t_fdf *s_fdf);
void		ft_param_bresen(t_fdf *s_fdf, t_point point_1, t_point point_2);

// ft_compute_map_dimensions.c
int			ft_free_line(char *line);
void		ft_skip_spaces(int *i, char *line);
int			ft_compute_current_x_size(char *line);
char		*ft_retrieve_line(int fd, int *y_size);
int			ft_compute_y_size(char **argv);

// ft_free_map.c
void		ft_free_map_array(int **map, int y_size);
void		ft_free_map_struct(t_fdf *s_fdf);

// ft_handle_error.c
void		ft_map_error(int **map, char *line, int i, int *x_sizes);
int			ft_strcmp(char *str1, char *str2);
void		ft_fdf_error(int **map, int y_size, t_fdf *s_fdf, int *x_sizes);

// ft_init_map_array.c
int			**ft_init_map(char **argv, int y_size, int *x_sizes);
char		*ft_init_current_line(int **map, int fd, int *x_sizes, int i);
void		ft_fill_map_line(int **map, int *x_sizes, char *line, int i);
int			ft_atoi(char *str, int *num_len);

// ft_init_s_fdf.c
t_fdf		*ft_init_s_fdf(int **map, int y_size, int *x_sizes);
t_point		**ft_convert_map_array_to_struct(int **map, t_fdf *s_fdf);
int			ft_get_z_range(int **map, t_fdf *s_fdf);

// get_next_line_utils.c
char		*ft_strjoin(char *str1, char *str2);
ssize_t		ft_strchr(char *str, char c);
char		*ft_strndup(char *str, ssize_t n);
ssize_t		ft_strlen(char *str);

// get_next_line.c
char		*get_next_line(int fd, int restart);
char		*ft_line_loop(int nb, char **result, char *buf, int fd);
void		ft_free(char **result);
char		*ft_get_line(char **result);
char		*ft_last_line(char **result);

#endif