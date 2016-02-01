/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 09:58:33 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 09:59:28 by cbarbisa         ###   ########.fr       */
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
