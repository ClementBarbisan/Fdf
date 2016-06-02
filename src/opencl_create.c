/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 10:14:13 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 10:15:09 by cbarbisa         ###   ########.fr       */
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
	if (cl_struct->nb_device > 1)
		cl_struct->devices[0] = cl_struct->devices[1];
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
