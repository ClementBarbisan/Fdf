/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wire.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:23:49 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 10:10:14 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	ft_draw_wire_opencl(t_mlx *m, int i, int j, int index)
{
	int	height1;
	int	height2;

	m->x1 = m->r_x[index + j];
	m->y1 = m->r_y[index + j];
	height1 = m->coords_z[index + j] * (20 * ((m->height + 1) / 2));
	if (j > 0)
	{
		m->x2 = m->r_x[index + j - 1];
		m->y2 = m->r_y[index + j - 1];
		height2 = m->coords_z[index + j - 1] * (20 * ((m->height + 1) / 2));
		ft_draw_line(m, height1, height2);
	}
	if (i + 1 < m->depth && j < m->l_c[i + 1])
	{
		m->x2 = m->r_x[index + m->l_c[i] + j];
		m->y2 = m->r_y[index + m->l_c[i] + j];
		height2 = m->coords_z[index + m->l_c[i] + j] * (20 * \
			((m->height + 1) / 2));
		ft_draw_line(m, height1, height2);
	}
}

void	ft_draw_square_opencl(t_mlx *m, int i, int j, int index)
{
	int		height1;
	int		height2;
	t_index	idx;
	int		k;

	k = 0;
	idx.i = i;
	idx.j = j;
	if (i + 1 < m->depth && j + 1 < m->l_c[i] && j + 1 < m->l_c[i + 1])
	{
		while (k < (int)m->scale * m->zoom)
		{
			height1 = ((m->coords_z[index + j] + (m->coords_z[index + j + 1] - \
				m->coords_z[index + j]) / (m->scale / m->zoom) * \
				k) * (20 * ((m->height + 1) / 2)));
			height2 = ((m->coords_z[index + m->l_c[i] + j] + \
				(m->coords_z[index + m->l_c[i] + j + 1] - \
				m->coords_z[index + m->l_c[i] + j]) / (m->scale /\
				m->zoom) * k) * (20 * ((m->height + 1) / 2)));
			set_points_opencl(m, idx, index, k);
			ft_draw_line(m, height1, height2);
			k++;
		}
	}
}

void	ft_draw_wire(t_mlx *m, float ***coords, int i, int j)
{
	int	height1;
	int	height2;

	m->x1 = set_coord(m, coords[i][j][0], coords[i][j][2], 1);
	m->y1 = set_coord(m, coords[i][j][1], coords[i][j][2], 0);
	height1 = m->coords[i][j][2] * (20 * ((m->height + 1) / 2));
	if (j > 0)
	{
		m->x2 = set_coord(m, coords[i][j - 1][0], coords[i][j - 1][2], 1);
		m->y2 = set_coord(m, coords[i][j - 1][1], coords[i][j - 1][2], 0);
		height2 = m->coords[i][j - 1][2] * (20 * ((m->height + 1) / 2));
		ft_draw_line(m, height1, height2);
	}
	if (i + 1 < m->depth && j < m->l_c[i + 1])
	{
		m->x2 = set_coord(m, coords[i + 1][j][0], coords[i + 1][j][2], 1);
		m->y2 = set_coord(m, coords[i + 1][j][1], coords[i + 1][j][2], 0);
		height2 = m->coords[i + 1][j][2] * (20 * ((m->height + 1) / 2));
		ft_draw_line(m, height1, height2);
	}
}

void	ft_draw_square(t_mlx *m, float ***coords, int i, int j)
{
	int		height1;
	int		height2;
	t_index	index;
	int		k;

	k = 0;
	index.i = i;
	index.j = j;
	if (i + 1 < m->depth && j + 1 < m->l_c[i] && j + 1 < m->l_c[i + 1])
	{
		while (k < m->scale * m->zoom)
		{
			height1 = ((m->coords[i][j][2] + (m->coords[i][j + 1][2] - \
				m->coords[i][j][2]) / (m->scale / m->zoom) * k) * (20 * \
				((m->height + 1) / 2)));
			height2 = ((m->coords[i + 1][j][2] + (m->coords[i + 1][j + 1][2] - \
				m->coords[i + 1][j][2]) / (m->scale / m->zoom) * k) * \
					(20 * ((m->height + 1) / 2)));
			set_points(m, index, k, coords);
			ft_draw_line(m, height1, height2);
			k++;
		}
	}
}
