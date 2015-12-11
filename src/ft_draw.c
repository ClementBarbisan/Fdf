/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:19:01 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/09 18:21:52 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <fdf.h>
#include <libft.h>

void		ft_pixel_put(t_img *img, int x, int y, int color)
{
	int		pos;

	pos = 0;
	if (x < WINWIDTH && x > 0 && y < WINHEIGHT && y > 0)
	{
		pos = y * img->size + 4 * x;
		img->data[pos] = (color >> 4) % 256;
		img->data[pos + 1] = (color >> 8) % 256;
		img->data[pos + 2] = color >> 16;
	}
}

int		ft_coord(t_line l, int x, int y)
{
	int	pixel;

	pixel = 0;
	if (l.y_max != l.y_min && l.x_max != l.x_min && y < x)
		pixel = l.y_min + ((l.y_max - l.y_min) * (l.x - l.x_min)) \
				/ (l.x_max - l.x_min);
	else if (l.y_max != l.y_min && l.x_max != l.x_min)
		pixel = l.x_min + ((l.x_max - l.x_min) * (l.y - l.y_min)) \
				/ (l.y_max - l.y_min);
	else if (l.y_min == l.y_max)
		pixel = l.y_min;
	else if (l.x_max == l.x_min)
		pixel = l.x_min;
	return (pixel);
}

void	ft_draw_x(t_mlx *m, t_line l, int x, int y)
{
	int		color;
	int		tmp_y;

	tmp_y = 0;
	color = 0xFFFFFFFF;
	while (((l.x < l.x_max && l.x_max - l.x_min > 0)
			|| (l.x > l.x_max && l.x_max - l.x_min < 0))
			&& l.x >= -20 && l.x <= WINWIDTH + 20)
	{
		tmp_y = ft_coord(l, x, y);
		if (l.x > 0 && l.x < WINWIDTH && tmp_y < WINHEIGHT && tmp_y > 0)
			ft_pixel_put(&m->img_struct, l.x, tmp_y, color);
		if (l.x > l.x_max)
			l.x--;
		else
			l.x++;
	}
}

void	ft_draw_y(t_mlx *m, t_line l, int x, int y)
{
	int		color;
	int		tmp_x;

	tmp_x = 0;
	color = 0xFFFFFF;
	while (((l.y < l.y_max && l.y_max - l.y_min > 0)
			|| (l.y > l.y_max && l.y_max - l.y_min < 0))
			&& l.y >= -20 && l.y <= WINHEIGHT + 20)
	{
		tmp_x = ft_coord(l, x, y);
		if (l.y > 0 && l.y < WINHEIGHT && tmp_x < WINWIDTH && tmp_x > 0)
			ft_pixel_put(&m->img_struct, tmp_x, l.y, color);
		if (l.y < l.y_max)
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
		ft_draw_x(m, l, x, y);
	else
		ft_draw_y(m, l, x, y);
}

t_line	ft_draw_init(t_mlx *m)
{
	t_line l;

	l.x_max = m->x1;
	l.x_min = m->x2;
	l.x = m->x2;
	l.y_max = m->y1;
	l.y_min = m->y2;
	l.y = m->y2;
	return (l);
}
