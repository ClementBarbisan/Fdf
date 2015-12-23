/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 09:01:05 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/23 17:34:09 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <OpenCL/cl.h>
#include <libft.h>

# define WINWIDTH 800
# define WINHEIGHT 600
# define SCALE 180
# define Z 3
# define PI 3.14159265358979323846

typedef struct			s_opencl
{
	cl_device_id		*devices;
	cl_command_queue	*queue;
	cl_context			context;
	cl_int				error;
	cl_kernel			kernel;
	cl_mem				*arg_kernel;
	size_t				nb_device;
}						t_opencl;

typedef struct	s_parse t_parse;

struct			s_parse
{
	int			number;
	char		*line;
	t_parse		*next;
	t_parse		*begin;
};

typedef struct	s_img
{
	char		*data;
	int 		bpp;
	int 		size;
	int 		endian;
}				t_img;

typedef struct	s_mlx
{
	int			scale;
	int			face_on;
	void		*mlx;
	void		*win;
	void		*img;
	t_img		img_struct;
	float		***coordinates;
	int*		line_count;
	double*		matrix;
	double*		scale_matrix;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	double		pos_x;
	double		pos_y;
	double		pos_z;
	double		zoom;
	double		rotation_x;
	double		rotation_y;
	double		rotation_z;
	int			height;
	int			width;
	int			depth;
}				t_mlx;

typedef struct	s_trigo
{
	double		cos_x;
	double		cos_y;
	double		cos_z;
	double		sin_x;
	double		sin_y;
	double		sin_z;
	double		cos_x_sin_y;
	double		sin_x_sin_y;
}				t_trigo;

typedef struct	s_line
{
	int			x_max;
	int			x_min;
	int			y_max;
	int			y_min;
	int			height1;
	int			height2;
	int			color;
	double		increment;
	int			x;
	int			y;
}				t_line;

void			free_stock(char ***stock);
float*			update_coordinates(float* coordinates, double* matrix, \
		double zoom);
void			ft_draw_wire(t_mlx *m, float*** coordinates, int i, int j);
void			ft_draw_square(t_mlx *m, float*** coordinates, int i, int j);
int				display(char ***stock, t_mlx m);
void			ft_draw_line(t_mlx *m, int height1, int height2);
int				ft_error(int argc, char **argv, int fd);
t_line			ft_draw_init(t_mlx *m, int height1, int height2);
void			update_matrix(t_mlx *m);
void			create_matrix(t_mlx *m);

#endif
