/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 15:24:03 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/14 14:17:16 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <fdf.h>

void	free_stock(char ***stock)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (stock[i] != NULL)
	{
		while (stock[i][j] != NULL)
		{
			free(stock[i][j]);
			stock[i][j] = NULL;
			j++;
		}
		free(stock[i]);
		stock[i] = NULL;
		j = 0;
		i++;
	}
	free(stock);
	stock = NULL;
}

char	***ft_parser(char **parse, t_mlx *m)
{
	int		i;
	char	***stock;

	i = 0;
	while (parse[i] != NULL)
		i++;
	stock = malloc(sizeof(char ***) * i + 1);
	i = 0;
	while (parse[i] != NULL)
	{
		stock[i] = malloc(sizeof(char **) * ft_strlen(parse[i]) + 1);
		stock[i] = ft_strsplit(parse[i], ' ');
		free(parse[i]);
		i++;
	}
	stock[i] = NULL;
	m->depth = i;
	return (stock);
}

int		count_line(int argc, char **argv, int fd)
{
	char	*line;
	int		count_line;

	count_line = 0;
	fd = ft_error(argc, argv, fd);
	if (fd == 0)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		free(line);
		line = NULL;
		count_line++;
	}
	if (line != NULL)
		free(line);
	close(fd);
	return (count_line);
}

void	fill_coordinates(char **parse, int face_on)
{
	char	***stock;
	t_mlx	m;

	m.face_on = face_on;
	stock = ft_parser(parse, &m);
	free(parse);
	display(stock, m);
}

char 	**fill_parse(int argc, char **argv)
{
	char	*line;
	char	**parse;
	int		fd;
	int		i;

	line = NULL;
	fd = 0;
	i = count_line(argc, argv, fd);
	parse = malloc(sizeof(char **) * i + 1);
	if (i <= 0 || (fd = ft_error(argc, argv, fd)) == 0)
		return (NULL);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		parse[i] = malloc(sizeof(char *) * ft_strlen(line) + 1);
		parse[i] = ft_strcpy(parse[i], line);
		free(line);
		line = NULL;
		i++;
	}
	if (line != NULL)
		free(line);
	parse[i] = NULL;
	close(fd);
	return (parse);
}

int		main(int argc, char **argv)
{
	char	**parse;
	int		face_on;

	face_on = 0;
	if (argc >= 3 && ft_strcmp(argv[2], "-face") == 0)
		face_on = 1;
	else if (argc >= 3)
	{
		ft_putendl("Wrong options.");
		return (0);
	}
	parse = fill_parse(argc, argv);
	if (parse == NULL)
		return (0);
	fill_coordinates(parse, face_on);
	return (0);
}

int		ft_error(int argc, char **argv, int fd)
{
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	else
	{
		ft_putstr("No file specified.\n");
		return (0);
	}
	if (fd == -1)
	{
		ft_putstr("File opening failed.\n");
		return (0);
	}
	return (fd);
}
