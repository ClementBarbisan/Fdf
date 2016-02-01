/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 17:09:55 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 10:17:27 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void					*ft_realloc(char *line, size_t size)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * (size + 1));
	while (line && line[i])
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	free(line);
	return (tmp);
}

char					*read_file(int fd)
{
	char	buffer[1024];
	int		ret;
	int		length;
	char	*line;

	line = NULL;
	ret = 0;
	length = 0;
	while ((ret = read(fd, buffer, 1024)) > 0)
	{
		length += ret;
		line = ft_realloc(line, sizeof(char) * length);
		line = ft_strcat(line, buffer);
		line[length] = '\0';
	}
	close(fd);
	return (line);
}

char					*open_file(char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		ft_putendl("Failed to open file");
		return (NULL);
	}
	line = read_file(fd);
	return (line);
}

void					add_kernel_to_program(t_opencl *opencl)
{
	opencl->kl_x[0] = clCreateKernel(opencl->program, \
		"compute_matrix", &opencl->err);
	opencl->kl_y[0] = clCreateKernel(opencl->program, \
		"compute_matrix", &opencl->err);
	opencl->kl_z[0] = clCreateKernel(opencl->program, \
		"compute_matrix", &opencl->err);
	opencl->r_x[0] = clCreateKernel(opencl->program, \
		"rasterize", &opencl->err);
	opencl->r_y[0] = clCreateKernel(opencl->program, \
		"rasterize", &opencl->err);
	if (opencl->err != CL_SUCCESS)
		ft_putendl("Failed to create kernel.");
}

void					initialize_opencl(t_mlx *m, t_opencl *opencl)
{
	opencl->err = 0;
	opencl->context = create_context(opencl);
	opencl->queue = create_commmand_queue(opencl);
	opencl->program = create_program(opencl, "./src/fdf.cl");
	if (opencl->program)
	{
		create_kernel(opencl);
		add_kernel_to_program(opencl);
		m->cl = opencl;
	}
	else
		m->cl = NULL;
}
