/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/16 09:30:25 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/29 10:52:58 by cbarbisa         ###   ########.fr       */
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
	m->cl->err = clEnqueueReadBuffer(m->cl->queue[0], m->buf[6], CL_FALSE, \
			0, m->count * sizeof(float), m->result_x, 0, NULL, NULL);
	m->cl->err = clEnqueueReadBuffer(m->cl->queue[0], m->buf[7], CL_FALSE, \
			0, m->count * sizeof(float), m->result_y, 0, NULL, NULL);
	m->cl->err = clEnqueueReadBuffer(m->cl->queue[0], m->buf[8], CL_TRUE, \
			0, m->count * sizeof(float), m->result_z, 0, NULL, NULL);
	if (m->cl->err != CL_SUCCESS)
	{
		ft_putendl("err on readd buffer coordinates");
		return;
	}
}

void	enqueue_kernel_coords(t_mlx *m)
{
	size_t *globalWorkSize;
	size_t tmp;
	size_t *localWorkSize;

	globalWorkSize = malloc(sizeof(size_t));
	localWorkSize = malloc(sizeof(size_t));
	globalWorkSize[0] = m->count;
	tmp = 512;
	while (m->count % tmp != 0)
		tmp--;
	localWorkSize[0] = tmp;
	m->cl->err = clEnqueueNDRangeKernel(m->cl->queue[0], m->cl->kl_x[0], 1, NULL, \
			globalWorkSize, localWorkSize, 0, NULL, NULL);
	m->cl->err = clEnqueueNDRangeKernel(m->cl->queue[0], m->cl->kl_y[0], 1, NULL, \
			globalWorkSize, localWorkSize, 0, NULL, NULL);
	m->cl->err = clEnqueueNDRangeKernel(m->cl->queue[0], m->cl->kl_z[0], 1, NULL, \
			globalWorkSize, localWorkSize, 0, NULL, NULL);
	if (m->cl->err != CL_SUCCESS)
	{
		ft_putendl("err on enqueue_kernel for coordinates");
		return;
	}
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
	{
		ft_putendl("err when setting kernel arguments coordinates");
		return;
	}
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
			m->buf[12], CL_FALSE, \
			0, m->count * sizeof(int), m->r_x, 0, NULL, NULL);
	m->cl->err = clEnqueueReadBuffer(m->cl->queue[0], \
			m->buf[13], CL_TRUE, \
			0, m->count * sizeof(int), m->r_y, 0, NULL, NULL);
	if (m->cl->err != CL_SUCCESS)
	{
		ft_putendl("err on readd buffer for rasterize");
		return;
	}
}

void	enqueue_kernel(t_mlx *m)
{
	size_t *globalWorkSize;
	size_t tmp;
	size_t *localWorkSize;

	globalWorkSize = malloc(sizeof(size_t));
	localWorkSize = malloc(sizeof(size_t));
	globalWorkSize[0] = m->count;
	tmp = 512;
	while (m->count % tmp != 0)
		tmp--;
	localWorkSize[0] = tmp;
	m->cl->err = clEnqueueNDRangeKernel(m->cl->queue[0], \
			m->cl->r_x[0], 1, NULL, \
			globalWorkSize, localWorkSize, 0, NULL, NULL);
	m->cl->err = clEnqueueNDRangeKernel(m->cl->queue[0], \
		m->cl->r_y[0], 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	if (m->cl->err != CL_SUCCESS)
	{
		ft_putendl("err on enqueue_kernel for rasterize");
		return;
	}
}

void	set_kernel_args_r(t_mlx *m)
{
	float width_win = WINWIDTH;
	float height_win = WINHEIGHT;
	float depth = Z;
	float width = m->width;
	float depthOffset = m->depth;
	m->cl->err = clSetKernelArg(m->cl->r_x[0], 0, sizeof(cl_mem), &m->buf[9]);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 1, sizeof(cl_mem), &m->buf[11]);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 2, sizeof(float), &depth);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 3, sizeof(float), &width);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 4, sizeof(float), &m->scale);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 5, sizeof(float), &width_win);
	m->cl->err |= clSetKernelArg(m->cl->r_x[0], 6, sizeof(cl_mem), &m->buf[12]);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 0, sizeof(cl_mem), &m->buf[10]);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 1, sizeof(cl_mem), &m->buf[11]);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 2, sizeof(float), &depth);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 3, sizeof(float), &depthOffset);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 4, sizeof(float), &m->scale);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 5, sizeof(float), &height_win);
	m->cl->err |= clSetKernelArg(m->cl->r_y[0], 6, sizeof(cl_mem), &m->buf[13]);
	if (m->cl->err != CL_SUCCESS)
	{
		ft_putendl("err on set args for rasterize");
		return;
	}
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

void	free_opencl(t_mlx *m)
{
	t_mlx *test;

	test = m;
}

void	update_opencl(t_mlx *m)
{
	update_matrix(m);
	copy_coords_opencl(m);
	update_img(m);
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
//	free_opencl(m);
	display_img(m);
	return (0);
}

int		expose_hook(t_mlx *m)
{
	int		i;
	int		j;
	float	***coords;

	i = 0;
	j = 0;
	update_matrix(m);
	coords = copy_coords(m);
	update_img(m);
	while (i < m->depth)
	{
		while (j < m->l_c[i])
		{
			if (m->face_on == 1)
				ft_draw_square(m, coords, i, j);
			else
				ft_draw_wire(m, coords, i, j);
			j++;
		}
		i++;
		j = 0;
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
			m->coords_x[index] = (float)((j - m->width / 2.0)) /\
									(float)m->width;
			m->coords_y[index] = (float)((i - m->depth / 2.0)) /\
									(float)m->depth;
			m->coords_z[index] = -(float)(ft_atoi(stock[i][j])) /\
						(float)(20.0 * ((m->height + 1) / 2));
			j++;
			index++;
		}
		i++;
		j = 0;
	}
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
