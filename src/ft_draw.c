/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:19:01 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/01/02 15:56:41 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void		ft_pixel_put(t_img *img, int x, int y, int color)
{
	int		pos;

	pos = y * img->size + 4 * x;
	img->data[pos] = (color >> 4) % 256;
	img->data[pos + 1] = (color >> 8) % 256;
	img->data[pos + 2] = color >> 16;
}

int			ft_coord(t_line l, int x, int y)
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

int			set_color(int height)
{
	int	color;

	color = 16777215 - (height * (42373567 / 50) % 16777215);
	return (color);
}

void		add_color(int p1, int p2, t_line *l)
{
	if (l->height1 > l->height2 && p1 > p2)
		l->color += ((float)(set_color(l->height1) - set_color(l->height2)) / \
				(float)(p1 - p2)) * l->increment;
	else if (l->height1 > l->height2 && p1 <= p2)
		l->color += ((float)(set_color(l->height1) - set_color(l->height2)) / \
				(float)(p2 - p1)) * l->increment;
	else if (l->height1 <= l->height2 && p1 > p2)
		l->color += ((float)(set_color(l->height2) - set_color(l->height1)) / \
				(float)(p1 - p2)) * l->increment;
	else if (l->height1 <= l->height2 && p1 <= p2)
		l->color += ((float)(set_color(l->height2) - set_color(l->height1)) / \
				(float)(p2 - p1)) * l->increment;
}

void		ft_draw_x(t_mlx *m, t_line l, int x, int y)
{
	int		tmp_y;
	int		shift;

	shift = 0;
	tmp_y = 0;
	while (((l.x < l.x_max && l.x_max - l.x_min > 0)
			|| (l.x > l.x_max && l.x_max - l.x_min < 0)))
	{
		tmp_y = ft_coord(l, x, y);
		if (l.x > 0 && l.x < WINWIDTH && tmp_y < WINHEIGHT && tmp_y > 0)
			ft_pixel_put(&m->img_struct, l.x, tmp_y + shift, l.color);
		if (l.x > l.x_max)
			l.x--;
		else
			l.x++;
		add_color(l.x_max, l.x_min, &l);
	}
}

void		ft_draw_y(t_mlx *m, t_line l, int x, int y)
{
	int		tmp_x;
	int		shift;

	shift = 0;
	tmp_x = 0;
	while (((l.y < l.y_max && l.y_max - l.y_min > 0)
			|| (l.y > l.y_max && l.y_max - l.y_min < 0)))
	{
		tmp_x = ft_coord(l, x, y);
		if (l.y > 0 && l.y < WINHEIGHT && tmp_x < WINWIDTH && tmp_x > 0)
			ft_pixel_put(&m->img_struct, tmp_x + shift, l.y, l.color);
		if (l.y < l.y_max)
			l.y++;
		else
			l.y--;
		add_color(l.y_max, l.y_min, &l);
	}
}

void		ft_draw_line(t_mlx *m, int height1, int height2)
{
	t_line	l;
	int		x;
	int		y;

	y = (m->y1 - m->y2) * (m->y1 - m->y2);
	x = (m->x1 - m->x2) * (m->x1 - m->x2);
	l = ft_draw_init(m, height1, height2);
	if (y < x)
		ft_draw_x(m, l, x, y);
	else
		ft_draw_y(m, l, x, y);
}

t_line		ft_draw_init(t_mlx *m, int height1, int height2)
{
	t_line l;

	l.height1 = height1;
	l.height2 = height2;
	l.x_max = m->x1;
	l.x_min = m->x2;
	l.x = m->x2;
	l.y_max = m->y1;
	l.y_min = m->y2;
	l.y = m->y2;
	l.increment = 0.0005;
	l.color = set_color(l.height1);
	return (l);
}
