/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:19:01 by cbarbisa          #+#    #+#             */
/*   Updated: 2013/12/22 22:02:44 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "fdf.h"
#include <libft.h>

t_line	ft_draw_init(t_mlx *m);

int		ft_y(t_line l, int x, int y)
{
	int	pixel;

	pixel = 0;
	if (l.yMx != l.yMn && l.xMx != l.xMn && y < x)
		pixel = l.yMn + ((l.yMx - l.yMn) * (l.x - l.xMn)) / (l.xMx - l.xMn);
	else if (l.yMx != l.yMn && l.xMx != l.xMn)
		pixel = l.xMn + ((l.xMx - l.xMn) * (l.y - l.yMn)) / (l.yMx - l.yMn);
	else if (l.yMn == l.yMx)
		pixel = l.yMn;
	else if (l.xMx == l.xMn)
		pixel = l.xMn;
	return (pixel);
}

void	ft_draw_x(t_mlx *m, t_line l)
{
	int		x;
	int		y;
	int		color;

	color = 0xFFFFFF;
	y = (m->y1 - m->y2) * (m->y1 - m->y2);
	x = (m->x1 - m->x2) * (m->x1 - m->x2);
	while ((l.x < l.xMx && l.xMx - l.xMn > 0)
			|| (l.x > l.xMx && l.xMx - l.xMn < 0))
	{
		mlx_pixel_put(m->mlx, m->win, l.x, ft_y(l, x, y), color);
		if (l.x > l.xMx)
			l.x--;
		else
			l.x++;
	}
}

void	ft_draw_y(t_mlx *m, t_line l)
{
	int		x;
	int		y;
	int		color;

	color = 0xFFFFFF;
	y = (m->y1 - m->y2) * (m->y1 - m->y2);
	x = (m->x1 - m->x2) * (m->x1 - m->x2);
	while ((l.y < l.yMx && l.yMx - l.yMn > 0)
			|| (l.y > l.yMx && l.yMx - l.yMn < 0))
	{
		mlx_pixel_put(m->mlx, m->win, ft_y(l, x, y), l.y, color);
		if (l.y < l.yMx)
			l.y++;
		else
			l.y--;
	}
}

void	ft_draw_line(t_mlx *m)
{
	t_line	l;
	int		x;
	int		y;

	y = (m->y1 - m->y2) * (m->y1 - m->y2);
	x = (m->x1 - m->x2) * (m->x1 - m->x2);
	l = ft_draw_init(m);
	if (y < x)
		ft_draw_x(m, l);
	else
		ft_draw_y(m, l);
}

t_line	ft_draw_init(t_mlx *m)
{
	t_line l;

	l.xMx = m->x1;
	l.xMn = m->x2;
	l.x = m->x2;
	l.yMx = m->y1;
	l.yMn = m->y2;
	l.y = m->y2;
	return (l);
}
