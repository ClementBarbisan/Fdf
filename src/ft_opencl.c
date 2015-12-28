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
			CL_DEVICE_TYPE_GPU, NULL, NULL, &cl_struct->error);
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
	size_t					size;
	size_t					i;

	i = 0;
	cl_struct->error = clGetDeviceIDs(cl_struct->platform_id, CL_DEVICE_TYPE_GPU,\
			 0, NULL, &cl_struct->nb_device);
	if (cl_struct->error != CL_SUCCESS || cl_struct->nb_device <= 0)
	{
		ft_putendl("Failed to get number of devices available.");
		return (NULL);
	}
	//test
	cl_struct->nb_device = 1;
	cl_struct->devices = malloc(sizeof(cl_device_id) * (cl_struct->nb_device / \
				sizeof(cl_device_id)));
	if (clGetDeviceIDs(cl_struct->platform_id, CL_DEVICE_TYPE_GPU, cl_struct->nb_device, \
				cl_struct->devices, NULL) != CL_SUCCESS)
	{
		ft_putendl("Failed to get device IDs.");
		return (NULL);
	}
	cl_struct->error = clGetDeviceInfo(cl_struct->devices[0], CL_DEVICE_MAX_WORK_GROUP_SIZE, 0, NULL, &size);
	cl_struct->error = clGetDeviceInfo(cl_struct->devices[0], CL_DEVICE_MAX_WORK_GROUP_SIZE, size, &cl_struct->maxGlobalWorkSize, 0);
	cl_struct->error = clGetDeviceInfo(cl_struct->devices[0], CL_DEVICE_MAX_WORK_ITEM_SIZES, 0, NULL, &size);
	cl_struct->maxWorkItemsSize = malloc(size);
	cl_struct->error = clGetDeviceInfo(cl_struct->devices[0], CL_DEVICE_MAX_WORK_ITEM_SIZES, size, cl_struct->maxWorkItemsSize, 0);

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
	file = open_file(filename);
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
		if (cl_struct->error == CL_INVALID_PROGRAM)
			ft_putendl("CL_INVALID_PROGRAM");
		else if (cl_struct->error == CL_INVALID_BINARY)
			ft_putendl("CL_INVALID_BINARY");
		else if (cl_struct->error == CL_BUILD_PROGRAM_FAILURE)
			ft_putendl("CL_BUILD_PROGRAM_FAILURE");
		cl_build_status status;
		size_t size;
		char	*programLog;
        clGetProgramBuildInfo(program, cl_struct->devices[0], CL_PROGRAM_BUILD_STATUS, 
                sizeof(cl_build_status), &status, NULL);
        clGetProgramBuildInfo(program, cl_struct->devices[0], 
                CL_PROGRAM_BUILD_LOG, 0, NULL, &size);
        programLog = (char*) calloc (size+1, sizeof(char));
        clGetProgramBuildInfo(program, cl_struct->devices[0], 
                CL_PROGRAM_BUILD_LOG, size+1, programLog, NULL);
        printf("Build failed; error=%d, status=%d, programLog:nn%s", 
                cl_struct->error, status, programLog);
        free(programLog);
		ft_putendl("Failed to build program.");
		return (NULL);
	}
	return (program);
}

void	initialize_opencl(t_mlx *m, t_opencl *opencl)
{
	cl_uint			i;

	i = 0;
	opencl->error = 0;
	opencl->context = create_context(opencl);
	opencl->queue = create_commmand_queue(opencl);
	opencl->program = create_program(opencl, "./src/fdf.cl");
	opencl->kernel_x = malloc(sizeof(cl_kernel) * opencl->nb_device);
	opencl->kernel_y = malloc(sizeof(cl_kernel) * opencl->nb_device);
	opencl->kernel_z = malloc(sizeof(cl_kernel) * opencl->nb_device);
	opencl->rasterize_x = malloc(sizeof(cl_kernel) * opencl->nb_device);
	opencl->rasterize_y = malloc(sizeof(cl_kernel) * opencl->nb_device);
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
	m->opencl = opencl;
}
