# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 17:49:54 by cbarbisa          #+#    #+#              #
#    Updated: 2014/06/10 17:15:25 by cbarbisa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c \
	ft_pow.c \
	ft_bzero.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memalloc.c \
	ft_memcpy.c \
	ft_memchr.c \
	ft_memcpy.c \
	ft_memdel.c \
	ft_memmove.c \
	ft_memset.c \
	ft_memcmp.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strclr.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdel.c \
	ft_strdup.c \
	ft_strequ.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strlcat.c \
	ft_strlen.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strncat.c \
	ft_strncmp.c \
	ft_strncpy.c \
	ft_strnequ.c \
	ft_strnew.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strstr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_memccpy.c \
	ft_putstr.c \
	ft_itoa.c \
	ft_strjoin.c \
	ft_strsplit.c \
	ft_strsub.c \
	ft_strtrim.c \
	ft_putendl.c \
	ft_putnbr.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstdelone.c \
	ft_lstdel.c \
	ft_lstadd.c \
	ft_lstiter.c \
	ft_lstmap.c \
	get_next_line.c \
	ft_ltoa.c \
	ft_lutoa.c \
	ft_utoa.c \
	ft_otoa.c \
	ft_lotoa.c \
	ft_htoa.c \
	ft_dtoa.c \
	ft_ftoa.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $^

%.o: %.c
	gcc -o $@ -c $^ -I./includes/ -Wall -Wextra -Werror

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
