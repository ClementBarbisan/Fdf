/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 09:30:25 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/01/30 17:16:35 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>

t_img	ft_img_init(t_mlx *m)
{
	t_img	img;
	char	*tmp;

	tmp = malloc(sizeof(char *));
	tmp = mlx_get_data_addr(m->img, &img.bpp, &img.size, &img.endian);
	img.data = tmp;
	return (img);
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

void	create_buffers_coords(t_mlx *m)
{
	m->buf = malloc(sizeof(cl_mem) * 14);
	m->buf[0] = clCreateBuffer(m->cl->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(float) * m->count, m->coords_x, NULL);
	m->buf[1] = clCreateBuffer(m->cl->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(float) * m->count, m->coords_y, NULL);
	m->buf[2] = clCreateBuffer(m->cl->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(float) * m->count, m->coords_z, NULL);
	m->buf[3] = clCreateBuffer(m->cl->context, CL_MEM_READ_ONLY | \
			CL_MEM_COPY_HOST_PTR, sizeof(float) * 4, m->matrix_x, NULL);
	m->buf[4] = clCreateBuffer(m->cl->context, CL_MEM_READ_ONLY | \
			CL_MEM_COPY_HOST_PTR, sizeof(float) * 4, m->matrix_y, NULL);
	m->buf[5] = clCreateBuffer(m->cl->context, CL_MEM_READ_ONLY | \
			CL_MEM_COPY_HOST_PTR, sizeof(float) * 4, m->matrix_z, NULL);
	m->buf[6] = clCreateBuffer(m->cl->context, CL_MEM_READ_WRITE, \
			sizeof(float) * m->count, NULL, NULL);
	m->buf[7] = clCreateBuffer(m->cl->context, CL_MEM_READ_WRITE, \
			sizeof(float) * m->count, NULL, NULL);
	m->buf[8] = clCreateBuffer(m->cl->context, CL_MEM_READ_WRITE, \
			sizeof(float) * m->count, NULL, NULL);
}

void	read_buffer_coords(t_mlx *m)
{
	m->result_x = malloc(sizeof(float) * m->count);
	m->result_y = malloc(sizeof(float) * m->count);
	m->result_z = malloc(sizeof(float) * m->count);
	m->cl->err = clEnqueueReadBuffer(m->cl->queue[0], m->buf[6], CL_TRUE, \
			0, m->count * sizeof(float), m->result_x, 0, NULL, NULL);
	m->cl->err |= clEnqueueReadBuffer(m->cl->queue[0], m->buf[7], CL_TRUE, \
			0, m->count * sizeof(float), m->result_y, 0, NULL, NULL);
	m->cl->err |= clEnqueueReadBuffer(m->cl->queue[0], m->buf[8], CL_TRUE, \
			0, m->count * sizeof(float), m->result_z, 0, NULL, NULL);
	if (m->cl->err != CL_SUCCESS)
		ft_putendl("err on readd buffer coordinates");
}

void	enqueue_kernel_coords(t_mlx *m)
{
	m->cl->err = clEnqueueNDRangeKernel(m->cl->queue[0], m->cl->kl_x[0], 1, \
		NULL, m->cl->global_work_size, m->cl->local_work_size, 0, NULL, NULL);
	m->cl->err |= clEnqueueNDRangeKernel(m->cl->queue[0], m->cl->kl_y[0], 1, \
		NULL, m->cl->global_work_size, m->cl->local_work_size, 0, NULL, NULL);
	m->cl->err |= clEnqueueNDRangeKernel(m->cl->queue[0], m->cl->kl_z[0], 1, \
		NULL, m->cl->global_work_size, m->cl->local_work_size, 0, NULL, NULL);
	if (m->cl->err != CL_SUCCESS)
		ft_putendl("err on enqueue_kernel for coordinates");
}

void	set_kernel_args_coords(t_mlx *m)
{
	m->cl->err = clSetKernelArg(m->cl->kl_x[0], 0, sizeof(float), &m->zoom);
	m->cl->err |= clSetKernelArg(m->cl->kl_x[0], 1, sizeof(cl_mem), &m->buf[3]);
	m->cl->err |= clSetKernelArg(m->cl->kl_x[0], 2, sizeof(cl_mem), &m->buf[0]);
	m->cl->err |= clSetKernelArg(m->cl->kl_x[0], 3, sizeof(cl_mem), &m->buf[1]);
	m->cl->err |= clSetKernelArg(m->cl->kl_x[0], 4, sizeof(cl_mem), &m->buf[2]);
	m->cl->err |= clSetKernelArg(m->cl->kl_x[0], 5, sizeof(cl_mem), &m->buf[6]);
	m->cl->err |= clSetKernelArg(m->cl->kl_y[0], 0, sizeof(float), &m->zoom);
	m->cl->err |= clSetKernelArg(m->cl->kl_y[0], 1, sizeof(cl_mem), &m->buf[4]);
	m->cl->err |= clSetKernelArg(m->cl->kl_y[0], 2, sizeof(cl_mem), &m->buf[0]);
	m->cl->err |= clSetKernelArg(m->cl->kl_y[0], 3, sizeof(cl_mem), &m->buf[1]);
	m->cl->err |= clSetKernelArg(m->cl->kl_y[0], 4, sizeof(cl_mem), &m->buf[2]);
	m->cl->err |= clSetKernelArg(m->cl->kl_y[0], 5, sizeof(cl_mem), &m->buf[7]);
	m->cl->err |= clSetKernelArg(m->cl->kl_z[0], 0, sizeof(float), &m->zoom);
	m->cl->err |= clSetKernelArg(m->cl->kl_z[0], 1, sizeof(cl_mem), &m->buf[5]);
	m->cl->err |= clSetKernelArg(m->cl->kl_z[0], 2, sizeof(cl_mem), &m->buf[0]);
	m->cl->err |= clSetKernelArg(m->cl->kl_z[0], 3, sizeof(cl_mem), &m->buf[1]);
	m->cl->err |= clSetKernelArg(m->cl->kl_z[0], 4, sizeof(cl_mem), &m->buf[2]);
	m->cl->err |= clSetKernelArg(m->cl->kl_z[0], 5, sizeof(cl_mem), &m->buf[8]);
	if (m->cl->err != CL_SUCCESS)
		ft_putendl("err when setting kernel arguments coordinates");
}

void	create_buffers_r(t_mlx *m)
{
	m->buf[9] = clCreateBuffer(m->cl->context, CL_MEM_READ_ONLY | \
			CL_MEM_COPY_HOST_PTR, sizeof(float) * m->count, m->result_x, NULL);
	m->buf[10] = clCreateBuffer(m->cl->context, CL_MEM_READ_ONLY | \
			CL_MEM_COPY_HOST_PTR, sizeof(float) * m->count, m->result_y, NULL);
	m->buf[11] = clCreateBuffer(m->cl->context, CL_MEM_READ_ONLY | \
			CL_MEM_COPY_HOST_PTR, sizeof(float) * m->count, m->result_z, NULL);
	m->buf[12] = clCreateBuffer(m->cl->context, CL_MEM_READ_WRITE, \
			sizeof(int) * m->count, NULL, NULL);
	m->buf[13] = clCreateBuffer(m->cl->context, CL_MEM_READ_WRITE, \
			sizeof(int) * m->count, NULL, NULL);
}

void	read_buffers(t_mlx *m)
{
	m->r_x = malloc(sizeof(int) * m->count);
	m->r_y = malloc(sizeof(int) * m->count);
	m->cl->err = clEnqueueReadBuffer(m->cl->queue[0], \
			m->buf[12], CL_TRUE, \
			0, m->count * sizeof(int), m->r_x, 0, NULL, NULL);
	m->cl->err |= clEnqueueReadBuffer(m->cl->queue[0], \
			m->buf[13], CL_TRUE, \
			0, m->count * sizeof(int), m->r_y, 0, NULL, NULL);
	if (m->cl->err != CL_SUCCESS)
		ft_putendl("err on readd buffer for rasterize");
}

void	enqueue_kernel(t_mlx *m)
{
	m->cl->err = clEnqueueNDRangeKernel(m->cl->queue[0], \
			m->cl->r_x[0], 1, NULL, \
			m->cl->global_work_size, m->cl->local_work_size, 0, NULL, NULL);
	m->cl->err |= clEnqueueNDRangeKernel(m->cl->queue[0], \
			m->cl->r_y[0], 1, NULL, m->cl->global_work_size, \
			m->cl->local_work_size, 0, NULL, NULL);
	if (m->cl->err != CL_SUCCESS)
		ft_putendl("err on enqueue_kernel for rasterize");
}

void	set_kernel_args_r(t_mlx *m)
{
	float width_win;
	float height_win;
	float depth;

	width_win = WINWIDTH;
	height_win = WINHEIGHT;
	depth = Z;
	m->cl->err = clSetKernelArg(m->cl->r_x[0], 0, sizeof(cl_mem), &m->buf[9]);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 1, sizeof(cl_mem), &m->buf[11]);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 2, sizeof(float), &depth);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 3, sizeof(int), &m->width);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 4, sizeof(float), &m->scale);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 5, sizeof(float), &width_win);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 6, sizeof(cl_mem), &m->buf[12]);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 0, sizeof(cl_mem), &m->buf[10]);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 1, sizeof(cl_mem), &m->buf[11]);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 2, sizeof(float), &depth);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 3, sizeof(int), &m->depth);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 4, sizeof(float), &m->scale);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 5, sizeof(float), &height_win);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 6, sizeof(cl_mem), &m->buf[13]);
	if (m->cl->err != CL_SUCCESS)
		ft_putendl("err on set args for rasterize");
}

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

void	free_mem_objects(t_mlx *m)
{
	int	i;

	i = 0;
	while (i < 14)
	{
		if (m->buf[i] != 0)
			clReleaseMemObject(m->buf[i]);
		i++;
	}
	free(m->result_x);
	free(m->result_y);
	free(m->result_z);
	free(m->r_x);
	free(m->r_y);
}

void	update_opencl(t_mlx *m)
{
	update_matrix(m);
	copy_coords_opencl(m);
	update_img(m);
}

void	release_img(t_mlx *m)
{
	free_mem_objects(m);
	display_img(m);
}

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

float	***update(int *i, int *j, float ***coords, t_mlx *m)
{
	if (m->r_hht == -1)
		*i = m->depth - 1;
	if (m->r_wth == -1)
		*j = m->l_c[*i] - 1;
	update_matrix(m);
	coords = copy_coords(m);
	update_img(m);
	return (coords);
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

double	compute_rotation(float radius)
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
	if (m->rotation_y > PI)
		m->r_wth = -1;
	else
		m->r_wth = 1;
	if (m->rotation_x < PI)
		m->r_hht = -1;
	else
		m->r_hht = 1;
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

void	free_command_queues(t_mlx *m)
{
	cl_uint	i;

	i = 0;
	while (i < m->cl->nb_device)
	{
		clReleaseCommandQueue(m->cl->queue[i]);
		i++;
	}
}

void	free_kernel(t_mlx *m)
{
	cl_uint	i;

	i = 0;
	while (i < m->cl->nb_device)
	{
		free(m->cl->kl_x[i]);
		free(m->cl->kl_y[i]);
		free(m->cl->kl_z[i]);
		free(m->cl->r_x[i]);
		free(m->cl->r_y[i]);
		i++;
	}
}

void	free_all(t_mlx *m)
{
	if (m->cl)
	{
		free_command_queues(m);
		free_kernel(m);
		clReleaseProgram(m->cl->program);
		clReleaseContext(m->cl->context);
	}
	else
		free_global_coordinates(m);
	free(m->l_c);
	free(m->matrix_x);
	free(m->matrix_y);
	free(m->matrix_z);
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
