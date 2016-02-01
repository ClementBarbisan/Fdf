# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 17:49:54 by cbarbisa          #+#    #+#              #
#*   Updated: 2015/12/02 16:38:01 by                  ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME = Fdf

SRC = $(addprefix ./src/,fdf.c \
	ft_parser.c \
	ft_draw_wire.c \
	ft_draw.c \
	ft_opencl.c \
	coords.c \
	coords_opencl.c \
	free.c \
	img.c \
	opencl_buffers.c \
	opencl_kernels.c \
	update_position.c \
	color_init.c \
	matrix.c \
	points.c \
	opencl_create.c \
	node.c)

OBJ = $(addprefix ./obj/, $(notdir $(SRC:.c=.o)))

all: compile $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^ -I./libft/includes -I./includes -L./ -lmlx \
		-framework OpenGL -framework AppKit -framework OpenCL -L./libft -lft

compile:
	make -C ./libft

./obj/%.o: ./src/%.c
	gcc -o $@ -c $^ -Wall -Werror -Wextra -I./libft/includes/ -I./includes

clean:
	/bin/rm -f $(OBJ)
	make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f ./libft/libft.a

re: fclean all

.PHONY: all, $(NAME), compile, ./obj/%.o, clean, fclean, re
