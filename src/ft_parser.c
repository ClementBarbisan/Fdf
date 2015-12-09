/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 15:24:03 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/09 17:06:19 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <fdf.h>

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
		count_line++;
	}
	close(fd);
	return (count_line);
}

void	fill_coordinates(char **parse)
{
	char	***stock;
	t_mlx	m;

	stock = ft_parser(parse, &m);
	free(parse);
	display(stock, m);
	free(stock);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	**parse;
	int		i;

	i = 0;
	line = NULL;
	fd = 0;
	i = count_line(argc, argv, fd);
	parse = malloc(sizeof(char **) * i + 1);
	if ((fd = ft_error(argc, argv, fd)) == 0 || i == -1)
		return (0);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		parse[i] = malloc(sizeof(char *) * ft_strlen(line) + 1);
		parse[i] = ft_strcpy(parse[i], line);
		free(line);
		i++;
	}
	parse[i] = NULL;
	close(fd);
	fill_coordinates(parse);
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
