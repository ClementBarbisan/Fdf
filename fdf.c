/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 09:30:25 by cbarbisa          #+#    #+#             */
/*   Updated: 2013/12/22 22:01:27 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
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
	int		j;
	int		tmp;
	int		yM;

	i = 0;
	j = 0;
	m->y1 = m->width/3 - 50;
	m->x2 = 0;
	m->y2 = 0;
	while (m->stock[i] != NULL)
	{
		m->x1 = (m->width/2 - 50) - (20 * i);
		while (m->stock[i][j] != NULL)
		{
			yM = ft_atoi(m->stock[i][j]);
			ft_putnbr(yM);
			ft_putstr("\n");
			m->y1 -= yM;
			ft_draw_wire(tmp, m, i, j);
			m->x1 += 20;
			m->y1 += 2 + yM;
			j++;
		}
		tmp = j;
		m->y1 += 20 - j * 2;
		j = 0;
		i++;
	}
	return (0);
}

int		ft_area(char ***stock)
{
	int		i;
	int		j;
	int		width;

	j = 0;
	i = 0;
	width = 0;
	while (stock[i] != NULL)
	{
		while (stock[i][j] != NULL)
		{
			if (j > width)
				width = j;
			j++;
		}
		j = 0;
		i++;
	}
	width = (i - 1) * 20 + width * 20 + 100;
	return (width);
}

int		display(char ***stock)
{
	t_mlx	m;

	m.stock = stock;
	m.width = ft_area(stock);
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, m.width, m.width, "Fdf");
	mlx_key_hook(m.win, key_hook, &m);
	mlx_expose_hook(m.win, expose_hook, &m);
	mlx_loop(m.mlx);
	return (0);
}
