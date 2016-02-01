/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 09:35:03 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 09:46:25 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

double	compute_rotation(float radius)
{
	if (radius > 2 * PI)
		return (0);
	else if (radius < 0)
		return (2 * PI);
	return (radius);
}

void	change_position(int keycode, t_mlx *m)
{
	if (keycode == 123)
		m->pos_x -= 0.05;
	else if (keycode == 124)
		m->pos_x += 0.05;
	else if (keycode == 125)
		m->pos_y += 0.05;
	else if (keycode == 126)
		m->pos_y -= 0.05;
}

void	change_rotation(int keycode, t_mlx *m)
{
	if (keycode == 12)
		m->rotation_y = compute_rotation(m->rotation_y + 0.1);
	else if (keycode == 13)
		m->rotation_y = compute_rotation(m->rotation_y - 0.1);
	else if (keycode == 14)
		m->rotation_x = compute_rotation(m->rotation_x + 0.1);
	else if (keycode == 15)
		m->rotation_x = compute_rotation(m->rotation_x - 0.1);
	if (m->rotation_y > PI)
		m->r_wth = -1;
	else
		m->r_wth = 1;
	if (m->rotation_x < PI)
		m->r_hht = -1;
	else
		m->r_hht = 1;
}

void	update_opencl(t_mlx *m)
{
	update_matrix(m);
	copy_coords_opencl(m);
	update_img(m);
}

float	***update(int *i, int *j, float ***coords, t_mlx *m)
{
	if (m->r_hht == -1)
		*i = m->depth - 1;
	if (m->r_wth == -1)
		*j = m->l_c[*i] - 1;
	update_matrix(m);
	coords = copy_coords(m);
	update_img(m);
	return (coords);
}
