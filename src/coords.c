/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 09:39:37 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 10:02:48 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

float	***copy_coords(t_mlx *m)
{
	float	***coords;
	int		i;
	int		j;

	i = 0;
	j = 0;
	coords = malloc(sizeof(float**) * m->depth);
	while (i < m->depth)
	{
		coords[i] = malloc(sizeof(float*) * m->l_c[i]);
		while (j < m->l_c[i])
		{
			coords[i][j] = update_coords(m->coords[i][j], \
					m);
			j++;
		}
		i++;
		j = 0;
	}
	return (coords);
}

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

void	free_global_coordinates(t_mlx *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < m->depth)
	{
		while (j < m->l_c[i])
		{
			free(m->coords[i][j]);
			j++;
		}
		free(m->coords[i]);
		i++;
		j = 0;
	}
	free(m->coords);
}

void	free_coords(float ***coords, t_mlx *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < m->depth)
	{
		while (j < m->l_c[i])
		{
			free(coords[i][j]);
			j++;
		}
		free(coords[i]);
		j = 0;
		i++;
	}
	free(coords);
}

void	ft_add_coords(t_mlx *m, char ***stock)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	m->coords = malloc(sizeof(float **) * m->depth);
	while (stock[i] != NULL)
	{
		m->coords[i] = malloc(sizeof(float *) * m->l_c[i]);
		while (stock[i][j] != NULL)
		{
			m->coords[i][j] = malloc(sizeof(float) * 3);
			m->coords[i][j][0] = (float)((j - m->width / 2.0)) /\
									(float)m->width;
			m->coords[i][j][1] = (float)((i - m->depth / 2.0)) /\
									(float)m->depth;
			m->coords[i][j][2] = -(float)(ft_atoi(stock[i][j])) /\
						(float)(20.0 * ((m->height + 1) / 2));
			j++;
		}
		i++;
		j = 0;
	}
}
