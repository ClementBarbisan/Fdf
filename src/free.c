/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 09:44:37 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 09:45:09 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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
