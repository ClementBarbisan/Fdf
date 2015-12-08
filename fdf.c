/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 09:30:25 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/08 17:44:10 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"
#include <libft.h>

int		key_hook(int keycode)
{
	if (keycode == 65307)
		exit (0);
	return (0);
}

int		expose_hook(t_mlx *m)
{
	int		i;

	i = 0;
	while (i < m->count)
	{
		m->x1 = (m->coordinates[i][0] / m->coordinates[i][2]) * m->width;
		m->y1 = (m->coordinates[i][1] / m->coordinates[i][2]) * m->depth;
		ft_draw_wire(m, i);
		i++;
	}
	return (0);
}

void		ft_area(t_mlx *m)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	while (m->stock[i] != NULL)
	{
		while (m->stock[i][j] != NULL)
		{
			count++;
			if (j > m->width)
				m->width = j;
			j++;
		}
		j = 0;
		i++;
	}
	m->depth = i;
	m->count = count;
}

void	ft_addCoordinates(t_mlx *m)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	m->coordinates = malloc(sizeof(float **) * m->count + 1);
	while (m->stock[i] != NULL)
	{
		while (m->stock[i][j] != NULL)
		{
			m->coordinates[count] = malloc(sizeof(float *) * 3);
			/*m->coordinates[count][2] = (float)(ft_atoi(m->stock[i][j]) + 3) / 10.0;*/
			m->coordinates[count][2] = (float)(1);
			m->coordinates[count][0] = (float)(j * 20 + 1) / (float)m->width;
			m->coordinates[count][1] = (float)(i * 20 + 1) / (float)m->depth;
			j++;
			count++;
		}
		i++;
		j = 0;
	}
}

int		display(char ***stock)
{
	t_mlx	m;

	m.stock = stock;
	m.count = 0;
	ft_area(&m);
	ft_addCoordinates(&m);
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, WINWIDTH, WINHEIGHT, "Fdf");
	mlx_key_hook(m.win, key_hook, &m);
	mlx_expose_hook(m.win, expose_hook, &m);
	mlx_loop(m.mlx);
	return (0);
}
