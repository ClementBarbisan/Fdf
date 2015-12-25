/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 09:30:25 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/25 17:29:03 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fdf.h>
#include <libft.h>

t_img	ft_img_init(t_mlx *m)
{
	t_img	img;
	char	*tmp;

	tmp = malloc(sizeof(char *));
	tmp = mlx_get_data_addr(m->img, &img.bpp, &img.size, &img.endian);
	img.data = tmp;
	return (img);
}

void	free_coordinates(float ***coordinates, t_mlx *m)
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

float	***copy_coordinates(t_mlx *m)
{
	float	***coordinates;
	int		i;
	int		j;

	i = 0;
	j = 0;
	coordinates = malloc(sizeof(float**) * m->depth);
	update_matrix(m);
	while (i < m->depth)
	{
		coordinates[i] = malloc(sizeof(float*) * m->line_count[i]);
		while (j < m->line_count[i])
		{
			coordinates[i][j] = update_coordinates(m->coordinates[i][j], \
					m->matrix, m->zoom);
			j++;
		}
		i++;
		j = 0;
	}
	i = 0;
	return (coordinates);
}

void	display_img(t_mlx *m)
{
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	mlx_destroy_image(m->mlx, m->img);
}

void	update_img(t_mlx *m)
{
	m->img = mlx_new_image(m->mlx, WINWIDTH, WINHEIGHT);
	m->img_struct = ft_img_init(m);
}

int		expose_hook(t_mlx *m)
{
	int		i;
	int		j;
	float	***coordinates;

	i = 0;
	j = 0;
	coordinates = copy_coordinates(m);
	update_img(m);
	while (i < m->depth)
	{
		while (j < m->line_count[i])
		{
			if (m->face_on == 1)
				ft_draw_square(m, coordinates, i, j);
			else
				ft_draw_wire(m, coordinates, i, j);
			j++;
		}
		i++;
		j = 0;
	}
	free_coordinates(coordinates, m);
	display_img(m);
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
}

int		key_hook(int keycode, t_mlx *m)
{
	if (keycode == 53)
	{
		mlx_destroy_window(m->mlx, m->win);
		exit(0);
	}
	else if (keycode >= 123 && keycode <= 126)
		change_position(keycode, m);
	else if (keycode == 35)
	{
		if (m->zoom < 4)
			m->zoom += 0.01;
	}
	else if (keycode == 31)
	{
		if (m->zoom > 0.1)
			m->zoom -= 0.01;
	}
	else if (keycode >= 12 && keycode <= 15)
		change_rotation(keycode, m);
	expose_hook(m);
	return (0);
}

void	ft_area(t_mlx *m, char ***stock)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	m->height = 1;
	m->width = 0;
	m->line_count = malloc(sizeof(int) * m->depth);
	while (stock[i] != NULL)
	{
		while (stock[i][j] != NULL)
		{
			if (-ft_atoi(stock[i][j]) > m->height)
				m->height = -ft_atoi(stock[i][j]);
			else if (ft_atoi(stock[i][j]) > m->height)
				m->height = ft_atoi(stock[i][j]);
			if (j > m->width)
				m->width = j;
			j++;
		}
		m->line_count[i] = j;
		j = 0;
		i++;
	}
}

void	ft_add_coordinates(t_mlx *m, char ***stock)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	m->coordinates = malloc(sizeof(float **) * m->depth);
	while (stock[i] != NULL)
	{
		m->coordinates[i] = malloc(sizeof(float *) * m->line_count[i]);
		while (stock[i][j] != NULL)
		{
			m->coordinates[i][j] = malloc(sizeof(float) * 3);
			m->coordinates[i][j][0] = (float)((j - m->width / 2.0)) /\
									(float)m->width;
			m->coordinates[i][j][1] = (float)((i - m->depth / 2.0)) /\
									(float)m->depth;
			m->coordinates[i][j][2] = -(float)(ft_atoi(stock[i][j])) /\
						(float)(20.0 * ((m->height + 1) / 2));
			j++;
		}
		i++;
		j = 0;
	}
}

int		display(char ***stock, t_mlx m)
{
	size_t	i;

	i = 0;
	ft_area(&m, stock);
	m.scale = SCALE / (m.width / 8);
	ft_add_coordinates(&m, stock);
	free_stock(stock);
	create_matrix(&m);
	m.opencl->kernel = malloc(sizeof(cl_kernel) * m.opencl->nb_device);
	/*while (i < m.opencl->nb_device)*/
	/*{*/
		/*m.opencl->kernel[i] = clCreateKernel(m.opencl->program, \*/
				/*"compute_matrix", &m.opencl->error);*/
		/*if (m.opencl->error != CL_SUCCESS)*/
		/*{*/
			/*ft_putendl("Failed to create kernel.");*/
			/*return (-1);*/
		/*}*/
		/*i++;*/
	/*}*/
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, WINWIDTH, WINHEIGHT, "Fdf");
	m.img = mlx_new_image(m.mlx, WINWIDTH, WINHEIGHT);
	mlx_hook(m.win, 2, 1, key_hook, &m);
	mlx_expose_hook(m.win, expose_hook, &m);
	mlx_loop(m.mlx);
	return (0);
}
