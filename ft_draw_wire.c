/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wire.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/22 20:23:49 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/08 18:10:53 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"
#include <libft.h>

void	ft_draw_wire(t_mlx *m, int i)
{
	if (i > 0 && m->coordinates[i - 1][1] == m->coordinates[i][1])
	{
		m->x2 = (m->coordinates[i - 1][0] / m->coordinates[i - 1][2]) * m->width;
		m->y2 = (m->coordinates[i - 1][1] / m->coordinates[i - 1][2]) * m->depth;
		ft_draw_line(m);
	}
	if (i + m->width + 1 < m->count)
	{
		m->x2 = (m->coordinates[i + m->width + 1][0] / m->coordinates[i + m->width + 1][2]) * m->width;
		m->y2 = (m->coordinates[i + m->width + 1][1] / m->coordinates[i + m->width + 1][2]) * m->depth;
		ft_draw_line(m);
	}
}
