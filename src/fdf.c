/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 09:30:25 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 09:54:32 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>

int		expose_hook_opencl(t_mlx *m)
{
	int		i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	index = 0;
	update_opencl(m);
	while (i < m->depth)
	{
		if (i > 0)
			index += m->l_c[i - 1];
		while (j < m->l_c[i])
		{
			if (m->face_on == 1)
				ft_draw_square_opencl(m, i, j, index);
			else
				ft_draw_wire_opencl(m, i, j, index);
			j++;
		}
		i++;
		j = 0;
	}
	release_img(m);
	return (0);
}

int		expose_hook(t_mlx *m)
{
	int		i;
	int		j;
	float	***coords;

	i = 0;
	j = 0;
	coords = NULL;
	coords = update(&i, &j, coords, m);
	while ((m->r_hht == -1 && i >= 0) || (m->r_hht == 1 && i < m->depth))
	{
		while ((m->r_wth == -1 && j >= 0) || (m->r_wth == 1 && j < m->l_c[i]))
		{
			if (m->face_on == 1)
				ft_draw_square(m, coords, i, j);
			else
				ft_draw_wire(m, coords, i, j);
			j += m->r_wth;
		}
		i += m->r_hht;
		j = m->r_wth == 1 ? 0 : m->l_c[i] - 1;
	}
	free_coords(coords, m);
	display_img(m);
	return (0);
}

int		key_hook(int keycode, t_mlx *m)
{
	if (keycode == 53)
	{
		mlx_destroy_window(m->mlx, m->win);
		free_all(m);
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
	if (m->cl)
		expose_hook_opencl(m);
	else
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
	m->l_c = malloc(sizeof(int) * m->depth);
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
		m->l_c[i] = j;
		j = 0;
		i++;
	}
}

int		display(char ***stock, t_mlx m)
{
	ft_area(&m, stock);
	m.scale = SCALE / ((m.width / 10) + 1);
	if (m.cl)
		ft_add_coords_opencl(&m, stock);
	else
		ft_add_coords(&m, stock);
	free_stock(stock);
	create_matrix(&m);
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, WINWIDTH, WINHEIGHT, "Fdf");
	m.img = mlx_new_image(m.mlx, WINWIDTH, WINHEIGHT);
	mlx_hook(m.win, 2, 1, key_hook, &m);
	if (m.cl)
		mlx_expose_hook(m.win, expose_hook_opencl, &m);
	else
		mlx_expose_hook(m.win, expose_hook, &m);
	mlx_loop(m.mlx);
	return (0);
}
