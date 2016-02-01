/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_buffers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 09:34:43 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 09:46:11 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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
