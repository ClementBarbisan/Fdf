/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 09:01:05 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/09 17:29:39 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINWIDTH 800
# define WINHEIGHT 600
# define SCALE 80
# define Z 3
# define PI 3.14159265358979323846

typedef struct 	s_img
{
	char		*data;
	int 		bpp;
	int 		size;
	int 		endian;
}				t_img;

typedef struct	s_mlx
{
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
	char		***stock;
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
	int			x;
	int			y;
}				t_line;

void			free_stock(char ***stock);
float*			update_coordinates(float* coordinates, double* matrix, \
		double zoom);
void			ft_draw_wire(t_mlx *m, float*** coordinates, int i, int j);
int				display(char ***stock, t_mlx m);
void			ft_draw_line(t_mlx *m);
int				ft_error(int argc, char **argv, int fd);
t_line			ft_draw_init(t_mlx *m);
void			update_matrix(t_mlx *m);
void			create_matrix(t_mlx *m);

#endif
