# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 12:25:12 by orazafy           #+#    #+#              #
#    Updated: 2023/06/11 21:43:45 by orazafy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
IFLAGS = -I$(INCDIR) -I$(MINILIBXDIR)
LIBS = $(MINILIBXDIR)/libmlx.a
LFLAGS = -lX11 -lXext -lm

SRCDIR = srcs
OBJDIR = objs
BINDIR = bin
INCDIR = include
MINILIBXDIR = minilibx

SRCS_FILES = fdf.c \
		ft_bresenham_utils.c \
		ft_bresenham.c \
		ft_compute_map_dimensions.c \
		ft_free_map.c \
		ft_handle_errors.c \
		ft_init_map_array.c \
		ft_init_s_fdf.c \
		get_next_line_utils.c \
		get_next_line.c

SRCS = $(addprefix $(SRCDIR)/, $(SRCS_FILES))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCS = $(INCDIR)/fdf.h

NAME = $(BINDIR)/fdf

RMR = rm -rf
MKDIR_P = mkdir -p

MLX = $(MINILIBXDIR)/libmlx.a

all: $(NAME)

$(MLX):
	cd $(MINILIBXDIR) && make

$(NAME): $(OBJS) $(MLX) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) $(LIBS) $(LFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS) | $(OBJDIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ 

 $(BINDIR):
	$(MKDIR_P) $(BINDIR)

$(OBJDIR):
	$(MKDIR_P) $(OBJDIR)

clean:
		$(RMR) $(OBJDIR)

fclean: clean
		$(RMR) $(BINDIR)
		$(RMR) $(LIBS)

re: fclean all

.PHONY: all clean fclean re