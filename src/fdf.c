/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 09:30:25 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/09 17:31:01 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fdf.h>
#include <libft.h>

void	free_coordinates(float*** coordinates, t_mlx *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < m->depth)
	{
		while (j < m->line_count[i])
		{
			free(coordinates[i][j]);
			j++;
		}
		free(coordinates[i]);
		j = 0;
		i++;
	}
	free(coordinates);
}

float***	copy_coordinates(t_mlx *m)
{
	float***	coordinates;
	int			i;
	int			j;

	i = 0;
	j = 0;
	coordinates = malloc(sizeof(float**) * m->depth);
	while (i < m->depth)
	{
		coordinates[i] = malloc(sizeof(float*) * m->line_count[i]);
		while (j < m->line_count[i])
		{
			coordinates[i][j] = update_coordinates(m->coordinates[i][j], m->matrix, m->zoom);
			j++;
		}
		i++;
		j = 0;
	}
	i = 0;
	return (coordinates);
}

int		expose_hook(t_mlx *m)
{
	int		i;
	int		j;
	float	***coordinates;

	i = 0;
	j = 0;
	update_matrix(m);
	coordinates = copy_coordinates(m);
	mlx_clear_window(m->mlx, m->win);
	while (i < m->depth)
	{
		while (j < m->line_count[i])
		{
			m->x1 = ((coordinates[i][j][0] / (coordinates[i][j][2] + Z)) *\
					m->width + m->width / 2) * SCALE;
			m->y1 = ((coordinates[i][j][1] / (coordinates[i][j][2] + Z)) *\
					m->depth + m->depth / 2) * SCALE;
			ft_draw_wire(m, coordinates, i, j);
			j++;
		}
		i++;
		j = 0;
	}
	free_coordinates(coordinates, m);
	return (0);
}

double	compute_rotation(double radius)
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
		m->pos_x -= 0.1;
	else if (keycode == 124)
		m->pos_x += 0.1;
	else if (keycode == 125)
		m->pos_y += 0.1;
	else if (keycode == 126)
		m->pos_y -= 0.1;
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
}

int		key_hook(int keycode, t_mlx *m)
{
	if (keycode == 53)
		exit(0);
	else if (keycode >= 123 && keycode <= 126)
		change_position(keycode, m);
	else if (keycode == 69)
	{
		if (m->zoom < 3)
			m->zoom += 0.1;
	}
	else if (keycode == 78)
	{
		if (m->zoom > 0.1)
			m->zoom -= 0.1;
	}
	else if (keycode >= 12 && keycode <= 15)
		change_rotation(keycode, m);
	expose_hook(m);
	return (0);
}

void	ft_area(t_mlx *m)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	m->height = 1;
	m->width = 0;
	m->line_count = malloc(sizeof(int) * m->depth);
	while (m->stock[i] != NULL)
	{
		while (m->stock[i][j] != NULL)
		{
			if (-ft_atoi(m->stock[i][j]) > m->height )
				m->height = -ft_atoi(m->stock[i][j]);
			else if (ft_atoi(m->stock[i][j]) > m->height)
				m->height = ft_atoi(m->stock[i][j]);
			if (j > m->width)
				m->width = j;
			j++;
		}
		m->line_count[i] = j;
		j = 0;
		i++;
	}
}

void	ft_add_coordinates(t_mlx *m)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	m->coordinates = malloc(sizeof(float **) * m->depth);
	while (m->stock[i] != NULL)
	{
		m->coordinates[i] = malloc(sizeof(float *) * m->line_count[i]);
		while (m->stock[i][j] != NULL)
		{
			m->coordinates[i][j] = malloc(sizeof(float) * 3);
			m->coordinates[i][j][0] = (float)((j - m->width / 2.0)) /\
									(float)m->width;
			m->coordinates[i][j][1] = (float)((i - m->depth / 2.0)) /\
									(float)m->depth;
			m->coordinates[i][j][2] = -(float)(ft_atoi(m->stock[i][j])) / \
						(float)(m->height) / (float)m->height;
			j++;
		}
		i++;
		j = 0;
	}
}

int		display(char ***stock, t_mlx m)
{
	m.stock = stock;
	ft_area(&m);
	ft_add_coordinates(&m);
	create_matrix(&m);
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, WINWIDTH, WINHEIGHT, "Fdf");
	mlx_key_hook(m.win, key_hook, &m);
	mlx_do_key_autorepeaton(&m);
	mlx_expose_hook(m.win, expose_hook, &m);
	mlx_loop(m.mlx);
	return (0);
}