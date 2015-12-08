/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 09:01:05 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/08 17:42:18 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINWIDTH 800
# define WINHEIGHT 600

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	int			count;
	float		**coordinates;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			width;
	int			depth;
	char		***stock;
}				t_mlx;

typedef struct	s_line
{
	int			xMx;
	int			xMn;
	int			yMx;
	int			yMn;
	int			x;
	int			y;
}				t_line;

void			ft_draw_wire(t_mlx *m, int i);
int				display(char ***stock);
void			ft_draw_line(t_mlx *m);

#endif
