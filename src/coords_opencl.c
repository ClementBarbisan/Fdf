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

size_t          findMultiple(size_t value, size_t div)
{
	while (div > 1 && value % div)
	div--;
	return (div);
}

void	set_work_size(t_mlx *m)
{
	size_t	tmp;
	size_t	multiple;
	size_t	current_multiple;

	multiple = findMultiple(m->count, 8);
	tmp = m->count;
	tmp /= multiple;
	multiple *= multiple;
	m->cl->global_work_size = malloc(sizeof(size_t) * 3);
	m->cl->local_work_size = malloc(sizeof(size_t) * 3);
	m->cl->global_work_size[0] = tmp;
	m->cl->global_work_size[1] = tmp;
	m->cl->global_work_size[2] = multiple;
	m->cl->local_work_size[0] = findMultiple(tmp, 32);
	m->cl->local_work_size[1] = findMultiple(tmp, 32);
	current_multiple = findMultiple(multiple, 64);
	while (m->cl->local_work_size[0] * m->cl->local_work_size[0] * current_multiple > 1024 && current_multiple > 1)
		current_multiple = findMultiple(multiple, current_multiple - 1);
	m->cl->local_work_size[2] = current_multiple;
}
