/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 10:18:35 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 10:19:34 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int			ft_ptrlength(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		i++;
	return (i);
}

char		***ft_parser(t_parse *parse, t_mlx *m)
{
	int		i;
	int		count;
	char	***stock;

	i = 0;
	count = parse->number;
	m->count = 0;
	stock = malloc(sizeof(char **) * (parse->number + 1));
	parse = parse->begin;
	while (parse != NULL && i < count)
	{
		stock[i] = ft_strsplit(parse->line, ' ');
		m->count += ft_ptrlength(stock[i]);
		parse = parse->next;
		i++;
	}
	stock[i] = NULL;
	m->depth = i;
	return (stock);
}

void		fill_coords(t_parse *parse, t_options options)
{
	char		***stock;
	t_opencl	opencl;
	t_mlx		m;

	m.r_wth = 1;
	m.r_hht = 1;
	m.face_on = options.faceon;
	if (options.opencl > 0)
		initialize_opencl(&m, &opencl);
	else
		m.cl = NULL;
	stock = ft_parser(parse, &m);
	free_parse(parse);
	display(stock, m);
}

t_parse		*add_node(t_parse *old_node, char *line)
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

t_parse		*fill_parse(int argc, char **argv)
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
