/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wire.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:23:49 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/09 18:23:41 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
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

int		check_value(t_mlx* m)
{
	if (m->x2 > 0 && m->x2 < WINWIDTH)
	{
		if (m->y2 > 0 && m->y2 < WINHEIGHT)
			return (1);
	}
	else if (m->x1 > 0 && m->x1 < WINWIDTH)
	{
		if (m->y1 > 0 && m->y1 < WINHEIGHT)
			return (1);
	}
	return (0);
}

void	ft_draw_wire(t_mlx *m, float ***coordinates, int i, int j)
{
	if (j > 0)
	{
		m->x2 = ((coordinates[i][j - 1][0] / (coordinates[i][j - 1][2] + Z)) *\
				m->width) * SCALE + WINWIDTH / 2;
		m->y2 = ((coordinates[i][j - 1][1] / (coordinates[i][j - 1][2] + Z)) *\
				m->depth) * SCALE + WINHEIGHT / 2;
		if (check_value(m) == 1)
			ft_draw_line(m);
	}
	if (i + 1 < m->depth && j < m->line_count[i + 1])
	{
		m->x2 = ((coordinates[i + 1][j][0] / (coordinates[i + 1][j][2] + Z)) *\
				m->width) * SCALE + WINWIDTH / 2;
		m->y2 = ((coordinates[i + 1][j][1] / (coordinates[i + 1][j][2] + Z)) *\
				m->depth) * SCALE + WINHEIGHT / 2;
		if (check_value(m) == 1)
			ft_draw_line(m);
	}
}
