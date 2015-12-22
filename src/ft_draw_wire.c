/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wire.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:23:49 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/21 17:47:50 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <fdf.h>
#include <libft.h>

float	*update_coordinates(float *coords, double *matrix, double zoom)
{
	float	*coordinates;

	coordinates = malloc(sizeof(float) * 3);
	coordinates[0] = (float)(coords[0] * matrix[0] + coords[1] * matrix[1] + \
			coords[2] * matrix[2] + matrix[3]);
	coordinates[1] = (float)(coords[0] * matrix[4] + coords[1] * matrix[5] + \
			coords[2] * matrix[6] + matrix[7]);
	coordinates[2] = (float)(coords[0] * matrix[8] + coords[1] * matrix[9] + \
			coords[2] * matrix[10] + matrix[11]);
	coordinates[0] *= (float)zoom;
	coordinates[1] *= (float)zoom;
	coordinates[2] *= (float)zoom;
	return (coordinates);
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
	m->matrix[0] = trigo.cos_y * trigo.cos_z;
	m->matrix[1] = -trigo.cos_y * trigo.sin_z;
	m->matrix[2] = trigo.sin_y;
	m->matrix[3] = m->pos_x;
	m->matrix[4] = trigo.sin_x_sin_y * trigo.cos_z + trigo.cos_x * trigo.sin_z;
	m->matrix[5] = -trigo.sin_x_sin_y * trigo.sin_z + trigo.cos_x * trigo.cos_z;
	m->matrix[6] = -trigo.sin_x * trigo.cos_y;
	m->matrix[7] = m->pos_y;
	m->matrix[8] = -trigo.cos_x_sin_y * trigo.cos_z + trigo.sin_x * trigo.sin_z;
	m->matrix[9] = trigo.cos_x_sin_y * trigo.sin_z + trigo.sin_x * trigo.cos_z;
	m->matrix[10] = trigo.cos_x * trigo.cos_y;
	m->matrix[11] = m->pos_z;
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
	m->matrix = malloc(sizeof(double) * 16);
	m->matrix[0] = 1;
	m->matrix[1] = 0;
	m->matrix[2] = 0;
	m->matrix[3] = 0;
	m->matrix[4] = 0;
	m->matrix[5] = 1;
	m->matrix[6] = 0;
	m->matrix[7] = 0;
	m->matrix[8] = 0;
	m->matrix[9] = 0;
	m->matrix[10] = 1;
	m->matrix[11] = 0;
	m->matrix[12] = 0;
	m->matrix[13] = 0;
	m->matrix[14] = 0;
	m->matrix[15] = 1;
}

int		set_coordinate(t_mlx *m, float xy, float z, int is_width)
{
	int	result;

	result = 0;
	if (is_width == 1)
		result = ((xy / (z + (float)Z)) * (float)m->width) * m->scale + WINWIDTH / 2;
	else
		result = ((xy / (z + (float)Z)) * (float)m->depth) * m->scale + WINHEIGHT / 2;
	return (result);
}

void	ft_draw_wire(t_mlx *m, float ***coordinates, int i, int j)
{
	int	height1;
	int	height2;

	m->x1 = set_coordinate(m, coordinates[i][j][0], coordinates[i][j][2], 1);
	m->y1 = set_coordinate(m, coordinates[i][j][1], coordinates[i][j][2], 0);
	height1 = m->coordinates[i][j][2] * (20 * ((m->height + 1) / 2));
	if (j > 0)
	{
		m->x2 = set_coordinate(m, coordinates[i][j - 1][0], coordinates[i][j - 1][2], 1);
		m->y2 = set_coordinate(m, coordinates[i][j - 1][1], coordinates[i][j - 1][2], 0);
		height2 = m->coordinates[i][j - 1][2] * (20 * ((m->height + 1) / 2));
		ft_draw_line(m, height1, height2);
	}
	if (i + 1 < m->depth && j < m->line_count[i + 1])
	{
		m->x2 = set_coordinate(m, coordinates[i + 1][j][0], coordinates[i + 1][j][2], 1);
		m->y2 = set_coordinate(m, coordinates[i + 1][j][1], coordinates[i + 1][j][2], 0);
		height2 = m->coordinates[i + 1][j][2] * (20 * ((m->height + 1) / 2));
		ft_draw_line(m, height1, height2);
	}
}

void	ft_draw_square(t_mlx *m, float ***coordinates, int i, int j)
{
	int		height1;
	int		height2;
	int		tmp_z;
	int		tmp_1;
	int		tmp_2;
	int		k;

	k = 0;
	tmp_z = 0;
	if (i + 1 < m->depth && j + 1 < m->line_count[i] && j + 1 < m->line_count[i + 1])
	{
		while (k < m->scale * m->zoom)
		{
			height1 = ((m->coordinates[i][j][2] + (m->coordinates[i][j + 1][2] - \
					m->coordinates[i][j][2]) / ((float)m->scale / (float)m->zoom) * (float)k) * (20 * ((m->height + 1) / 2)));
			height2 = ((m->coordinates[i + 1][j][2] + (m->coordinates[i + 1][j + 1][2] - \
					m->coordinates[i + 1][j][2]) / ((float)m->scale / (float)m->zoom) * (float)k) * (20 * ((m->height + 1) / 2)));
			tmp_z = coordinates[i][j][2] + (coordinates[i][j + 1][2] - \
					coordinates[i][j][2]) / (float)m->scale / (float)m->zoom * ((float)k / (float)(20.0 * ((m->height + 1) / 2)));
			tmp_1 = set_coordinate(m, coordinates[i][j][0], coordinates[i][j][2], 1);
			tmp_2 = set_coordinate(m, coordinates[i][j + 1][0], coordinates[i][j + 1][2], 1);
			m->x1 = tmp_1 + ((float)(tmp_2 - tmp_1) / (float)m->scale / (float)m->zoom) * k;
			tmp_1 = set_coordinate(m, coordinates[i][j][1], coordinates[i][j][2], 0);
			tmp_2 = set_coordinate(m, coordinates[i][j + 1][1], coordinates[i][j + 1][2], 0);
			m->y1 = tmp_1 + ((float)(tmp_2 - tmp_1) / (float)m->scale / (float)m->zoom) * k;
			tmp_z = coordinates[i + 1][j][2] + (coordinates[i + 1][j + 1][2] \
					- coordinates[i + 1][j][2]) / (float)m->scale / (float)m->zoom * ((float)k / (float)(20.0 * ((m->height + 1) / 2)));
			tmp_1 = set_coordinate(m, coordinates[i + 1][j][0], coordinates[i + 1][j][2], 1);
			tmp_2 = set_coordinate(m, coordinates[i + 1][j + 1][0], coordinates[i + 1][j + 1][2], 1);
			m->x2 = tmp_1 + ((float)(tmp_2 - tmp_1) / (float)m->scale / (float)m->zoom) * k;
			tmp_1 = set_coordinate(m, coordinates[i + 1][j][1], coordinates[i + 1][j][2], 0);
			tmp_2 = set_coordinate(m, coordinates[i + 1][j + 1][1], coordinates[i + 1][j + 1][2], 0);
			m->y2 = tmp_1 + ((float)(tmp_2 - tmp_1) / (float)m->scale / (float)m->zoom) * k;
			ft_draw_line(m, height1, height2);
			k++;
		}
	}
}
