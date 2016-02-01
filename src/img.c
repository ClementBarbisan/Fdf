/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 09:43:52 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/02/01 09:46:06 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_img	ft_img_init(t_mlx *m)
{
	t_img	img;
	char	*tmp;

	tmp = malloc(sizeof(char *));
	tmp = mlx_get_data_addr(m->img, &img.bpp, &img.size, &img.endian);
	img.data = tmp;
	return (img);
}

void	display_img(t_mlx *m)
{
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	mlx_destroy_image(m->mlx, m->img);
}

void	update_img(t_mlx *m)
{
	m->img = mlx_new_image(m->mlx, WINWIDTH, WINHEIGHT);
	m->img_struct = ft_img_init(m);
}

void	release_img(t_mlx *m)
{
	free_mem_objects(m);
	display_img(m);
}
