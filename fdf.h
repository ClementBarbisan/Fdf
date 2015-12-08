/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 09:01:05 by cbarbisa          #+#    #+#             */
/*   Updated: 2013/12/22 22:02:56 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			width;
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

void			ft_draw_wire(int tmp, t_mlx *m, int i, int j);
int				display(char ***stock);
void			ft_draw_line(t_mlx *m);

#endif
