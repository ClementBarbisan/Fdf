/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 10:08:48 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 10:10:05 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		set_coord(t_mlx *m, float xy, float z, int is_width)
{
	int	result;

	result = 0;
	if (is_width == 1)
		result = ((xy / (z + (float)Z)) * m->width) * m->scale + WINWIDTH / 2;
	else
		result = ((xy / (z + (float)Z)) * m->depth) * m->scale + WINHEIGHT / 2;
	return (result);
}

int		get_index(int *count_line, int i, int j)
{
	int count;
	int k;

	k = 0;
	count = 0;
	while (k < i)
	{
		count += count_line[k];
		k++;
	}
	j--;
	if (j >= 0)
		count += j;
	return (count);
}

void	set_points_opencl(t_mlx *m, t_index idx, int index, int k)
{
	m->x1 = m->r_x[index + idx.j] + ((m->r_x[index + idx.j + 1] - \
		m->r_x[index + idx.j]) / m->scale / m->zoom) * k;
	m->y1 = m->r_y[index + idx.j] + ((m->r_y[index + idx.j + 1] - \
		m->r_y[index + idx.j]) / m->scale / m->zoom) * k;
	m->x2 = m->r_x[index + m->l_c[idx.i] + idx.j] + ((m->r_x[index + \
		m->l_c[idx.i] + idx.j + 1] - m->r_x[index + m->l_c[idx.i] + idx.j]) / \
		m->scale / m->zoom) * k;
	m->y2 = m->r_y[index + m->l_c[idx.i] + idx.j] + ((m->r_y[index + \
		m->l_c[idx.i] + idx.j + 1] - m->r_y[index + m->l_c[idx.i] + idx.j]) / \
		m->scale / m->zoom) * k;
}

void	set_points(t_mlx *m, t_index idx, int k, float ***coords)
{
	int	tmp_1;
	int	tmp_2;

	tmp_1 = set_coord(m, coords[idx.i][idx.j][0], coords[idx.i][idx.j][2], 1);
	tmp_2 = set_coord(m, coords[idx.i][idx.j + 1][0], coords[idx.i][idx.j + 1]\
			[2], 1);
	m->x1 = tmp_1 + ((tmp_2 - tmp_1) / m->scale / m->zoom) * k;
	tmp_1 = set_coord(m, coords[idx.i][idx.j][1], coords[idx.i][idx.j][2], 0);
	tmp_2 = set_coord(m, coords[idx.i][idx.j + 1][1], coords[idx.i][idx.j + 1]\
			[2], 0);
	m->y1 = tmp_1 + ((tmp_2 - tmp_1) / m->scale / m->zoom) * k;
	tmp_1 = set_coord(m, coords[idx.i + 1][idx.j][0], coords[idx.i + 1][idx.j]\
			[2], 1);
	tmp_2 = set_coord(m, coords[idx.i + 1][idx.j + 1][0], coords[idx.i + 1]\
			[idx.j + 1][2], 1);
	m->x2 = tmp_1 + ((tmp_2 - tmp_1) / m->scale / m->zoom) * k;
	tmp_1 = set_coord(m, coords[idx.i + 1][idx.j][1], coords[idx.i + 1][idx.j]\
			[2], 0);
	tmp_2 = set_coord(m, coords[idx.i + 1][idx.j + 1][1], coords[idx.i + 1]\
			[idx.j + 1][2], 0);
	m->y2 = tmp_1 + ((tmp_2 - tmp_1) / m->scale / m->zoom) * k;
}
