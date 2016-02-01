/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 09:01:05 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 10:22:13 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <OpenCL/cl.h>
# include <math.h>
# include <libft.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <fcntl.h>

# define WINWIDTH 800
# define WINHEIGHT 600
# define SCALE 180
# define Z 3
# define PI 3.14159265358979323846

typedef struct			s_options
{
	int					faceon;
	int					opencl;
}						t_options;

typedef struct s_parse	t_parse;

struct					s_parse
{
	int					number;
	char				*line;
	t_parse				*next;
	t_parse				*begin;
};

typedef struct			s_img
{
	char				*data;
	int					bpp;
	int					size;
	int					endian;
}						t_img;

typedef struct			s_opencl
{
	cl_device_id		*devices;
	cl_platform_id		platform_id;
	cl_command_queue	*queue;
	cl_program			program;
	cl_context			context;
	cl_int				err;
	cl_kernel			*kl_x;
	cl_kernel			*kl_y;
	cl_kernel			*kl_z;
	cl_kernel			*r_x;
	cl_kernel			*r_y;
	size_t				*global_work_size;
	size_t				*local_work_size;
	cl_uint				nb_device;
}						t_opencl;

typedef struct			s_mlx
{
	int					r_wth;
	int					r_hht;
	float				scale;
	int					face_on;
	void				*mlx;
	void				*win;
	void				*img;
	t_img				img_struct;
	float				***coords;
	int					*r_x;
	int					*r_y;
	float				*coords_x;
	float				*coords_y;
	float				*coords_z;
	float				*result_x;
	float				*result_y;
	float				*result_z;
	int					*l_c;
	float				*matrix_w;
	float				*matrix_x;
	float				*matrix_y;
	float				*matrix_z;
	float				*scale_matrix;
	int					x1;
	int					x2;
	int					y1;
	int					y2;
	float				pos_x;
	float				pos_y;
	float				pos_z;
	float				zoom;
	double				rotation_x;
	double				rotation_y;
	double				rotation_z;
	int					height;
	int					width;
	int					depth;
	int					count;
	cl_mem				*buf;
	t_opencl			*cl;
}						t_mlx;

typedef struct			s_index
{
	int					i;
	int					j;
}						t_index;

typedef struct			s_trigo
{
	double				cos_x;
	double				cos_y;
	double				cos_z;
	double				sin_x;
	double				sin_y;
	double				sin_z;
	double				cos_x_sin_y;
	double				sin_x_sin_y;
}						t_trigo;

typedef struct			s_line
{
	int					x_max;
	int					x_min;
	int					y_max;
	int					y_min;
	int					height1;
	int					height2;
	int					color;
	double				increment;
	int					x;
	int					y;
}						t_line;

void					ft_draw_square_opencl(t_mlx *m, int i, int j, int \
							index);
void					ft_draw_wire_opencl(t_mlx *m, int i, int j, int index);
void					ft_draw_wire(t_mlx *m, float ***coords, int i, int j);
void					ft_draw_square(t_mlx *m, float ***coords, int i, int j);

void					initialize_opencl(t_mlx *m, t_opencl *opencl);
void					*ft_realloc(char *line, size_t size);
char					*read_file(int fd);
char					*open_file(char *filename);
void					add_kernel_to_program(t_opencl *opencl);

void					free_stock(char ***stock);
int						ft_error(int argc, char **argv, int fd);
void					free_parse(t_parse *parse);
t_options				check_options(int argc, char **argv, t_options options);

int						expose_hook_opencl(t_mlx *m);
int						expose_hook(t_mlx *m);
int						key_hook(int keycode, t_mlx *m);
void					ft_area(t_mlx *m, char ***stock);
int						display(char ***stock, t_mlx m);

float					***copy_coords(t_mlx *m);
void					free_global_coordinates(t_mlx *m);
void					free_coords(float ***coords, t_mlx *m);
void					ft_add_coords(t_mlx *m, char ***stock);
float					*update_coords(float *coords, t_mlx *m);

void					copy_coords_opencl(t_mlx *m);
void					ft_add_coords_opencl(t_mlx *m, char ***stock);
void					set_work_size(t_mlx *m);

void					free_command_queues(t_mlx *m);
void					free_all(t_mlx *m);
void					free_mem_objects(t_mlx *m);

t_img					ft_img_init(t_mlx *m);
void					display_img(t_mlx *m);
void					update_img(t_mlx *m);
void					release_img(t_mlx *m);

void					create_buffers_coords(t_mlx *m);
void					read_buffer_coords(t_mlx *m);
void					create_buffers_r(t_mlx *m);
void					read_buffers(t_mlx *m);

void					enqueue_kernel_coords(t_mlx *m);
void					set_kernel_args_coords(t_mlx *m);
void					enqueue_kernel(t_mlx *m);
void					set_kernel_args_r(t_mlx *m);
void					free_kernel(t_mlx *m);

double					compute_rotation(float radius);
void					change_position(int keycode, t_mlx *m);
void					change_rotation(int keycode, t_mlx *m);
void					update_opencl(t_mlx *m);
float					***update(int *i, int *j, float ***coords, t_mlx *m);

int						ft_coord(t_line l, int x, int y);
void					ft_draw_x(t_mlx *m, t_line l, int x, int y);
void					ft_draw_y(t_mlx *m, t_line l, int x, int y);
void					ft_draw_line(t_mlx *m, int height1, int height2);

void					ft_pixel_put(t_img *img, int x, int y, int color);
int						set_color(int height);
void					add_color(int p1, int p2, t_line *l);
t_line					ft_draw_init(t_mlx *m, int height1, int height2);

t_trigo					create_trigo(t_mlx *m);
void					update_matrix(t_mlx *m);
void					malloc_matrix(t_mlx *m);
void					create_matrix(t_mlx *m);

int						set_coord(t_mlx *m, float xy, float z, int is_width);
int						get_index(int *count_line, int i, int j);
void					set_points_opencl(t_mlx *m, t_index idx, int index, \
							int k);
void					set_points(t_mlx *m, t_index idx, int k, \
							float ***coords);

cl_context				create_context(t_opencl *cl_struct);
cl_command_queue		*create_commmand_queue(t_opencl *cl_struct);
cl_program				create_program(t_opencl *cl_struct, char *filename);
void					create_kernel(t_opencl *opencl);

int						ft_ptrlength(char **ptr);
char					***ft_parser(t_parse *parse, t_mlx *m);
void					fill_coords(t_parse *parse, t_options options);
t_parse					*add_node(t_parse *old_node, char *line);
t_parse					*fill_parse(int argc, char **argv);

#endif
