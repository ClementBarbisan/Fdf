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

SRC = fdf.c \
	ft_parser.c \
	ft_draw_wire.c \
	ft_draw.c

OBJ = $(SRC:.c=.o)

all: compile $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^ -I./libft/includes -I./ -L./ -lmlx -framework OpenGL -framework AppKit -L./libft -lft

compile:
	make -C ./libft

%.o: %.c
	gcc -o $@ -c $^ -Wall -Werror -Wextra -I./libft/includes/ -I./

clean:
	/bin/rm -f $(OBJ)
	make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
