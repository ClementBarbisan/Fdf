/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 17:09:55 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/26 18:28:01 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>

cl_context		create_context(t_opencl *cl_struct)
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
			CL_DEVICE_TYPE_GPU, NULL, NULL, &cl_struct->error);
	if (cl_struct->error != CL_SUCCESS)
	{
		ft_putendl("Can't create OpenCL context for GPU, trying CPU...");
		context = clCreateContextFromType(context_properties, \
			CL_DEVICE_TYPE_CPU, NULL, NULL, &cl_struct->error);
		if (cl_struct->error != CL_SUCCESS)
		{
			ft_putendl("Can't create OpenCL context for GPU, trying CPU...");
			return (NULL);
		}
	}
	return (context);
}

void	*ft_realloc(char *line, size_t size)
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
	size_t					i;

	i = 0;
	cl_struct->error = clGetDeviceIDs(cl_struct->platform_id, CL_DEVICE_TYPE_GPU,\
			 0, NULL, &cl_struct->nb_device);
	if (cl_struct->error != CL_SUCCESS || cl_struct->nb_device <= 0)
	{
		ft_putendl("Failed to get number of devices available.");
		return (NULL);
	}
	cl_struct->devices = malloc(sizeof(cl_device_id) * (cl_struct->nb_device / \
				sizeof(cl_device_id)));
	if (clGetDeviceIDs(cl_struct->platform_id, CL_DEVICE_TYPE_GPU, cl_struct->nb_device, \
				cl_struct->devices, NULL) != CL_SUCCESS)
	{
		ft_putendl("Failed to get device IDs.");
		return (NULL);
	}
	queue = malloc(sizeof(cl_command_queue) * cl_struct->nb_device);
	while (i < cl_struct->nb_device)
	{
		queue[i] = clCreateCommandQueue(cl_struct->context, \
				cl_struct->devices[i], 0, NULL);
		i++;
	}
	return (queue);
}

cl_program	create_program(t_opencl *cl_struct, char *filename)
{
	cl_program				program;
	char					*file;
	char					*options = "-cl-fast-relaxed-math";

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
	cl_struct->error = clBuildProgram(program, cl_struct->nb_device, \
			cl_struct->devices, options, NULL, NULL);
	if (cl_struct->error != CL_SUCCESS)
	{
		ft_putendl("Failed to build program.");
		return (NULL);
	}
	return (program);
}

void	create_kernel(t_opencl *opencl)
{
	opencl->kernel_x = malloc(sizeof(cl_kernel) * opencl->nb_device);
	opencl->kernel_y = malloc(sizeof(cl_kernel) * opencl->nb_device);
	opencl->kernel_z = malloc(sizeof(cl_kernel) * opencl->nb_device);
	opencl->rasterize_x = malloc(sizeof(cl_kernel) * opencl->nb_device);
	opencl->rasterize_y = malloc(sizeof(cl_kernel) * opencl->nb_device);
}

void	add_kernel_to_program(t_opencl *opencl)
{
	size_t	i;

	i = 0;
	while (i < opencl->nb_device)
	{
		opencl->kernel_x[i] = clCreateKernel(opencl->program, \
		"compute_matrix", &opencl->error);
		opencl->kernel_y[i] = clCreateKernel(opencl->program, \
			"compute_matrix", &opencl->error);
		opencl->kernel_z[i] = clCreateKernel(opencl->program, \
			"compute_matrix", &opencl->error);
		opencl->rasterize_x[i] = clCreateKernel(opencl->program, \
					"rasterize", &opencl->error);
		opencl->rasterize_y[i] = clCreateKernel(opencl->program, \
		"rasterize", &opencl->error);
		if (opencl->error != CL_SUCCESS)
			ft_putendl("Failed to create kernel.");
		i++;
	}
}

void	initialize_opencl(t_mlx *m, t_opencl *opencl) {
	opencl->error = 0;
	opencl->context = create_context(opencl);
	opencl->queue = create_commmand_queue(opencl);
	opencl->program = create_program(opencl, "./src/fdf.cl");
	if (opencl->program)
	{
		create_kernel(opencl);
		add_kernel_to_program(opencl);
		m->opencl = opencl;
	}
	else
		m->opencl = NULL;
}
