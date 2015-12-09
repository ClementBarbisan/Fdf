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
	ft_draw.c)

OBJ = $(addprefix ./obj/, $(notdir $(SRC:.c=.o)))

all: compile $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^ -I./libft/includes -I./includes -L./ -lmlx \
		-framework OpenGL -framework AppKit -L./libft -lft

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
