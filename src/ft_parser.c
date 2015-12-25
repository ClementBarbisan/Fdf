/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 15:24:03 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/25 17:19:58 by cbarbisa         ###   ########.fr       */
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

void	free_parse(t_parse *parse)
{
	t_parse	*old_node;

	parse = parse->begin;
	while (parse != NULL)
	{
		old_node = parse;
		free(old_node->line);
		free(old_node);
		parse = parse->next;
	}
}

char	***ft_parser(t_parse *parse, t_mlx *m)
{
	int		i;
	int		count;
	char	***stock;

	i = 0;
	count = parse->number;
	stock = malloc(sizeof(char **) * (parse->number + 1));
	parse = parse->begin;
	while (parse != NULL && i < count)
	{
		stock[i] = ft_strsplit(parse->line, ' ');
		parse = parse->next;
		i++;
	}
	stock[i] = NULL;
	m->depth = i;
	return (stock);
}

void	fill_coordinates(t_parse *parse, int face_on, t_opencl *opencl)
{
	char	***stock;
	t_mlx	m;

	m.face_on = face_on;
	m.opencl = opencl;
	stock = ft_parser(parse, &m);
	free_parse(parse);
	display(stock, m);
}

t_parse	*add_node(t_parse *old_node, char *line)
{
	t_parse	*node;

	node = malloc(sizeof(t_parse));
	node->line = malloc(sizeof(char) * ft_strlen(line) + 1);
	node->line = ft_strcpy(node->line, line);
	node->next = NULL;
	if (old_node == NULL)
	{
		node->begin = node;
		node->number = 1;
	}
	else
	{
		old_node->next = node;
		node->begin = old_node->begin;
		node->number = ++old_node->number;
	}
	free(line);
	line = NULL;
	return (node);
}

t_parse	*fill_parse(int argc, char **argv)
{
	char	*line;
	t_parse	*parse;
	int		fd;

	line = NULL;
	fd = 0;
	parse = NULL;
	if ((fd = ft_error(argc, argv, fd)) == 0)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
		parse = add_node(parse, line);
	if (line != NULL)
		free(line);
	close(fd);
	return (parse);
}

int		main(int argc, char **argv)
{
	t_parse	*parse;
	t_opencl	opencl;
	int		face_on;

	face_on = 0;
	parse = NULL;
	if (argc >= 3 && ft_strcmp(argv[2], "-face") == 0)
		face_on = 1;
	else if (argc >= 3)
	{
		ft_putendl("Wrong options.");
		return (0);
	}
	if (argc > 1)
	{
		parse = fill_parse(argc, argv);
		if (parse == NULL)
		{
			ft_putendl("Parsing failed.");
			return (0);
		}
		initialize_opencl(&opencl);
		fill_coordinates(parse, face_on, &opencl);
	}
	else
		ft_putendl("Not enough arguments.");
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
