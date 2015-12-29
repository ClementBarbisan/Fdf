/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wire.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:23:49 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/29 10:54:42 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <fdf.h>
#include <libft.h>
#include <stdio.h>

float	*update_coords(float *coords, t_mlx *m)
{
	float	*update_coords;

	update_coords = malloc(sizeof(float) * 3);
	update_coords[0] = (float)(coords[0] * m->matrix_x[0] + coords[1] * \
			m->matrix_x[1] + coords[2] * m->matrix_x[2] + m->matrix_x[3]);
	update_coords[1] = (float)(coords[0] * m->matrix_y[0] + coords[1] * \
			m->matrix_y[1] + coords[2] * m->matrix_y[2] + m->matrix_y[3]);
	update_coords[2] = (float)(coords[0] * m->matrix_z[0] + coords[1] * \
			m->matrix_z[1] + coords[2] * m->matrix_z[2] + m->matrix_z[3]);
	update_coords[0] *= (float)m->zoom;
	update_coords[1] *= (float)m->zoom;
	update_coords[2] *= (float)m->zoom;
	return (update_coords);
}

t_trigo	create_trigo(t_mlx *m)
{
	t_trigo	trigo;

	trigo.cos_x = cos(m->rotation_x);
	trigo.cos_y = cos(m->rotation_y);
	trigo.cos_z = cos(m->rotation_z);
	trigo.sin_x = sin(m->rotation_x);
	trigo.sin_y = sin(m->rotation_y);
	trigo.sin_z = sin(m->rotation_z);
	trigo.cos_x_sin_y = trigo.cos_x * trigo.sin_y;
	trigo.sin_x_sin_y = trigo.sin_x * trigo.sin_y;
	return (trigo);
}

void	update_matrix(t_mlx *m)
{
	t_trigo	trigo;

	trigo = create_trigo(m);
	m->matrix_x[0] = trigo.cos_y * trigo.cos_z;
	m->matrix_x[1] = -trigo.cos_y * trigo.sin_z;
	m->matrix_x[2] = trigo.sin_y;
	m->matrix_x[3] = m->pos_x;
	m->matrix_y[0] = trigo.sin_x_sin_y * trigo.cos_z + trigo.cos_x * \
					 trigo.sin_z;
	m->matrix_y[1] = -trigo.sin_x_sin_y * trigo.sin_z + trigo.cos_x * \
					 trigo.cos_z;
	m->matrix_y[2] = -trigo.sin_x * trigo.cos_y;
	m->matrix_y[3] = m->pos_y;
	m->matrix_z[0] = -trigo.cos_x_sin_y * trigo.cos_z + trigo.sin_x * \
					 trigo.sin_z;
	m->matrix_z[1] = trigo.cos_x_sin_y * trigo.sin_z + trigo.sin_x * \
					 trigo.cos_z;
	m->matrix_z[2] = trigo.cos_x * trigo.cos_y;
	m->matrix_z[3] = m->pos_z;
}

void	create_matrix(t_mlx *m)
{
	m->rotation_x = PI * 1.75;
	m->rotation_y = 0.25;
	m->rotation_z = 0;
	m->pos_x = 0;
	m->pos_y = 0;
	m->pos_z = 0;
	m->zoom = 1;
	m->matrix_w = malloc(sizeof(float) * 4);
	m->matrix_x = malloc(sizeof(float) * 4);
	m->matrix_y = malloc(sizeof(float) * 4);
	m->matrix_z = malloc(sizeof(float) * 4);
	m->matrix_x[0] = 1;
	m->matrix_x[1] = 0;
	m->matrix_x[2] = 0;
	m->matrix_x[3] = 0;
	m->matrix_y[0] = 0;
	m->matrix_y[1] = 1;
	m->matrix_y[2] = 0;
	m->matrix_y[3] = 0;
	m->matrix_z[0] = 0;
	m->matrix_z[1] = 0;
	m->matrix_z[2] = 1;
	m->matrix_z[3] = 0;
	m->matrix_w[0] = 0;
	m->matrix_w[1] = 0;
	m->matrix_w[2] = 0;
	m->matrix_w[3] = 1;
}

int		set_coordinate(t_mlx *m, float xy, float z, int is_width)
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
	int		k;

	k = 0;
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
			m->x1 = m->r_x[index + j] + ((m->r_x[index + j + 1] - \
				m->r_x[index + j])  / m->scale / m->zoom) * k;
			m->y1 = m->r_y[index + j] + ((m->r_y[index + j + 1] - \
				m->r_y[index + j]) / m->scale / m->zoom) * k;
			m->x2 = m->r_x[index + m->l_c[i] + j] + ((m->r_x[index + m->l_c[i] \
				+ j + 1] - m->r_x[index + m->l_c[i] + j])  / m->scale / \
					m->zoom) * k;
			m->y2 =  m->r_y[index + m->l_c[i] + j] + (( m->r_y[index + \
				m->l_c[i] + j + 1] - m->r_y[index + m->l_c[i] + j])  / \
					m->scale / m->zoom) * k;
			ft_draw_line(m, height1, height2);
			k++;
		}
	}
}

void	ft_draw_wire(t_mlx *m, float ***coords, int i, int j)
{
	int	height1;
	int	height2;

	m->x1 = set_coordinate(m, coords[i][j][0], coords[i][j][2], 1);
	m->y1 = set_coordinate(m, coords[i][j][1], coords[i][j][2], 0);
	height1 = m->coords[i][j][2] * (20 * ((m->height + 1) / 2));
	if (j > 0)
	{
		m->x2 = set_coordinate(m, coords[i][j - 1][0], coords[i][j - 1][2], 1);
		m->y2 = set_coordinate(m, coords[i][j - 1][1], coords[i][j - 1][2], 0);
		height2 = m->coords[i][j - 1][2] * (20 * ((m->height + 1) / 2));
		ft_draw_line(m, height1, height2);
	}
	if (i + 1 < m->depth && j < m->l_c[i + 1])
	{
		m->x2 = set_coordinate(m, coords[i + 1][j][0], coords[i + 1][j][2], 1);
		m->y2 = set_coordinate(m, coords[i + 1][j][1], coords[i + 1][j][2], 0);
		height2 = m->coords[i + 1][j][2] * (20 * ((m->height + 1) / 2));
		ft_draw_line(m, height1, height2);
	}
}

void	ft_draw_square(t_mlx *m, float ***coords, int i, int j)
{
	int		height1;
	int		height2;
	int		tmp_1;
	int		tmp_2;
	int		k;

	k = 0;
	if (i + 1 < m->depth && j + 1 < m->l_c[i] && j + 1 < m->l_c[i + 1])
	{
		while (k < m->scale * m->zoom)
		{
			height1 = ((m->coords[i][j][2] + (m->coords[i][j + 1][2] - \
				m->coords[i][j][2]) / (m->scale / m->zoom) * k) * (20 * ((m->height + 1) / 2)));
			height2 = ((m->coords[i + 1][j][2] + (m->coords[i + 1][j + 1][2] - \
				m->coords[i + 1][j][2]) / (m->scale / m->zoom) * k) * (20 * ((m->height + 1) / 2)));
			tmp_1 = set_coordinate(m, coords[i][j][0], coords[i][j][2], 1);
			tmp_2 = set_coordinate(m, coords[i][j + 1][0], coords[i][j + 1][2], 1);
			m->x1 = tmp_1 + ((tmp_2 - tmp_1) / m->scale / m->zoom) * k;
			tmp_1 = set_coordinate(m, coords[i][j][1], coords[i][j][2], 0);
			tmp_2 = set_coordinate(m, coords[i][j + 1][1], coords[i][j + 1][2], 0);
			m->y1 = tmp_1 + ((tmp_2 - tmp_1) / m->scale / m->zoom) * k;
			tmp_1 = set_coordinate(m, coords[i + 1][j][0], coords[i + 1][j][2], 1);
			tmp_2 = set_coordinate(m, coords[i + 1][j + 1][0], coords[i + 1][j + 1][2], 1);
			m->x2 = tmp_1 + ((tmp_2 - tmp_1) / m->scale / m->zoom) * k;
			tmp_1 = set_coordinate(m, coords[i + 1][j][1], coords[i + 1][j][2], 0);
			tmp_2 = set_coordinate(m, coords[i + 1][j + 1][1], coords[i + 1][j + 1][2], 0);
			m->y2 = tmp_1 + ((tmp_2 - tmp_1) / m->scale / m->zoom) * k;
			ft_draw_line(m, height1, height2);
			k++;
		}
	}
}
