/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 15:24:03 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/03/03 17:14:08 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void		free_stock(char ***stock)
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

void		free_parse(t_parse *parse)
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

t_options	check_options(int argc, char **argv, t_options options)
{
	int		i;

	i = 2;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-face") == 0)
			options.faceon = 1;
		else if (ft_strcmp(argv[i], "-opencl") == 0)
			options.opencl = 1;
		i++;
	}
	if (options.faceon == -1 && options.opencl == -1)
		ft_putendl("Wrong options[-opencl -face].");
	return (options);
}

int			main(int argc, char **argv)
{
	t_parse		*parse;
	t_options	options;

	parse = NULL;
	options.faceon = -1;
	options.opencl = -1;
	if (argc >= 3)
		options = check_options(argc, argv, options);
	if (argc >= 3 && options.faceon == -1 && options.opencl == -1)
		return (0);
	if (argc > 1)
	{
		parse = fill_parse(argc, argv);
		if (parse == NULL)
		{
			ft_putendl("Parsing failed.");
			return (0);
		}
		fill_coords(parse, options);
	}
	else
		ft_putendl("Usage : ./Fdf <filename> [-opencl -face]");
	return (0);
}

int			ft_error(int argc, char **argv, int fd)
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
