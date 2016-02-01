/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords_opencl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 09:39:15 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 09:45:41 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	copy_coords_opencl(t_mlx *m)
{
	create_buffers_coords(m);
	set_kernel_args_coords(m);
	enqueue_kernel_coords(m);
	read_buffer_coords(m);
	create_buffers_r(m);
	set_kernel_args_r(m);
	enqueue_kernel(m);
	read_buffers(m);
}

void	ft_add_coords_opencl(t_mlx *m, char ***stock)
{
	int		i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	index = 0;
	m->coords_x = malloc(sizeof(float) * m->count);
	m->coords_y = malloc(sizeof(float) * m->count);
	m->coords_z = malloc(sizeof(float) * m->count);
	while (stock[i] != NULL)
	{
		while (stock[i][j] != NULL)
		{
			m->coords_x[index] = (float)(j - m->width / 2.0) / (float)m->width;
			m->coords_y[index] = (float)(i - m->depth / 2.0) / (float)m->depth;
			m->coords_z[index] = -(float)(ft_atoi(stock[i][j])) /\
						(float)(20.0 * ((m->height + 1) / 2));
			j++;
			index++;
		}
		i++;
		j = 0;
	}
	set_work_size(m);
}

void	set_work_size(t_mlx *m)
{
	size_t	tmp;

	tmp = 512;
	m->cl->global_work_size = malloc(sizeof(size_t));
	m->cl->local_work_size = malloc(sizeof(size_t));
	m->cl->global_work_size[0] = m->count;
	while (m->count % tmp != 0)
		tmp--;
	m->cl->local_work_size[0] = tmp;
}
