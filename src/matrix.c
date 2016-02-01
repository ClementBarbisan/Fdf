/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 10:02:27 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 10:13:32 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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

void	malloc_matrix(t_mlx *m)
{
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

void	create_matrix(t_mlx *m)
{
	m->rotation_x = PI * 1.75;
	m->rotation_y = 0.25;
	m->rotation_z = 0;
	m->pos_x = 0;
	m->pos_y = 0;
	m->pos_z = 0;
	m->zoom = 1;
	malloc_matrix(m);
}
