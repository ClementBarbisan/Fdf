/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wire.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:23:49 by cbarbisa          #+#    #+#             */
/*   Updated: 2013/12/22 22:03:42 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "fdf.h"
#include <libft.h>

void	ft_draw_wire(int tmp, t_mlx *m, int i, int j)
{
	int		yM;

	yM = ft_atoi(m->stock[i][j]);
	if (j > 0)
	{
		m->x2 = m->x1 - 20;
		m->y2 = m->y1 + yM - ft_atoi(m->stock[i][j - 1]);
		ft_draw_line(m);
	}
	if (i > 0 && j < tmp)
	{
		m->x2 = m->x1 + 20;
		m->y2 = m->y1 - 20 + yM - ft_atoi(m->stock[i - 1][j]);
		ft_draw_line(m);
	}
}
