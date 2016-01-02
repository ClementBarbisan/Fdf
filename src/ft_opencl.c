/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 17:09:55 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/01/02 16:19:50 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

cl_context				create_context(t_opencl *cl_struct)
{
	cl_uint					nb_platforms;
	cl_context_properties	*context_properties;
	cl_context				context;

	if (clGetPlatformIDs(1, &cl_struct->platform_id, &nb_platforms) != \
			CL_SUCCESS || &nb_platforms <= 0)
	{
		ft_putendl("No OpenCL platform detected.");
		return (NULL);
	}
	context_properties = malloc(sizeof(cl_context_properties) * 3);
	context_properties[0] = CL_CONTEXT_PLATFORM;
	context_properties[1] = (cl_context_properties)cl_struct->platform_id;
	context_properties[2] = 0;
	context = clCreateContextFromType(context_properties, \
			CL_DEVICE_TYPE_GPU, NULL, NULL, &cl_struct->err);
	if (cl_struct->err != CL_SUCCESS)
	{
		ft_putendl("Can't create OpenCL context for GPU...");
		return (NULL);
	}
	return (context);
}

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

cl_command_queue		*create_commmand_queue(t_opencl *cl_struct)
{
	cl_command_queue		*queue;

	cl_struct->err = clGetDeviceIDs(cl_struct->platform_id, CL_DEVICE_TYPE_GPU,\
			0, NULL, &cl_struct->nb_device);
	if (cl_struct->err != CL_SUCCESS || cl_struct->nb_device <= 0)
	{
		ft_putendl("Failed to get number of devices available.");
		return (NULL);
	}
	cl_struct->devices = malloc(sizeof(cl_device_id) * (cl_struct->nb_device / \
				sizeof(cl_device_id)));
	if (clGetDeviceIDs(cl_struct->platform_id, CL_DEVICE_TYPE_GPU, \
				cl_struct->nb_device, cl_struct->devices, NULL) != CL_SUCCESS)
	{
		ft_putendl("Failed to get device IDs.");
		return (NULL);
	}
	queue = malloc(sizeof(cl_command_queue));
	queue[0] = clCreateCommandQueue(cl_struct->context, \
				cl_struct->devices[0], 0, NULL);
	return (queue);
}

cl_program				create_program(t_opencl *cl_struct, char *filename)
{
	cl_program				program;
	char					*file;

	file = NULL;
	program = NULL;
	if ((file = open_file(filename)) != NULL)
		program = clCreateProgramWithSource(cl_struct->context, 1,
											(const char**)&file,
											NULL, NULL);
	if (program == NULL)
	{
		ft_putendl("Failed to create program from source.");
		return (NULL);
	}
	cl_struct->err = clBuildProgram(program, cl_struct->nb_device, \
			cl_struct->devices, NULL, NULL, NULL);
	if (cl_struct->err != CL_SUCCESS)
	{
		ft_putendl("Failed to build program.");
		return (NULL);
	}
	free(file);
	return (program);
}

void					create_kernel(t_opencl *opencl)
{
	opencl->kl_x = malloc(sizeof(cl_kernel));
	opencl->kl_y = malloc(sizeof(cl_kernel));
	opencl->kl_z = malloc(sizeof(cl_kernel));
	opencl->r_x = malloc(sizeof(cl_kernel));
	opencl->r_y = malloc(sizeof(cl_kernel));
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
