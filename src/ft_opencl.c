/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 17:09:55 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/25 17:26:21 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

cl_context		create_context(t_opencl *cl_struct)
{
	cl_uint					nb_platforms;
	cl_context_properties	*context_properties;

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
	cl_struct->context = clCreateContextFromType(context_properties, \
			CL_DEVICE_TYPE_GPU, NULL, NULL, &cl_struct->error);
	if (cl_struct->error != CL_SUCCESS)
	{
		ft_putendl("Can't create OpenCL context for GPU, trying CPU...");
		cl_struct->context = clCreateContextFromType(context_properties, \
			CL_DEVICE_TYPE_GPU, NULL, NULL, &cl_struct->error);
		if (cl_struct->error != CL_SUCCESS)
		{
			ft_putendl("Can't create OpenCL context for GPU, trying CPU...");
			return (NULL);
		}
	}
	return (cl_struct->context);
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
	cl_struct->queue = malloc(sizeof(cl_command_queue) * cl_struct->nb_device);
	while (i < cl_struct->nb_device)
	{
		cl_struct->queue[0] = clCreateCommandQueue(cl_struct->context, \
				cl_struct->devices[0], 0, NULL);
		i++;
	}
	return (cl_struct->queue);
}

cl_program	create_program(t_opencl *cl_struct, char *filename)
{
	cl_program				program;
	char					*file;

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
			cl_struct->devices, NULL, NULL, NULL);
	if (cl_struct->error != CL_SUCCESS)
	{
		ft_putendl("Failed to build program.");
		return (NULL);
	}
	return (cl_struct->program);
}

void	initialize_opencl(t_opencl *opencl)
{
	int			i;

	i = 0;
	opencl->context = create_context(opencl);
	opencl->queue = create_commmand_queue(opencl);
	opencl->program = create_program(opencl, "./src/fdf.cl");
}
