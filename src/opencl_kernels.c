/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_kernels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 09:34:48 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 09:46:18 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	enqueue_kernel_coords(t_mlx *m)
{
	m->cl->err = clEnqueueNDRangeKernel(m->cl->queue[0], m->cl->kl_x[0], 3, \
		NULL, m->cl->global_work_size, m->cl->local_work_size, 0, NULL, NULL);
	m->cl->err |= clEnqueueNDRangeKernel(m->cl->queue[0], m->cl->kl_y[0], 3, \
		NULL, m->cl->global_work_size, m->cl->local_work_size, 0, NULL, NULL);
	m->cl->err |= clEnqueueNDRangeKernel(m->cl->queue[0], m->cl->kl_z[0], 3, \
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

void	enqueue_kernel(t_mlx *m)
{
	m->cl->err = clEnqueueNDRangeKernel(m->cl->queue[0], \
			m->cl->r_x[0], 3, NULL, \
			m->cl->global_work_size, m->cl->local_work_size, 0, NULL, NULL);
	m->cl->err |= clEnqueueNDRangeKernel(m->cl->queue[0], \
			m->cl->r_y[0], 3, NULL, m->cl->global_work_size, \
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
