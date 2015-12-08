/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 08:58:29 by cbarbisa          #+#    #+#             */
/*   Updated: 2013/11/30 11:15:06 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	int	i1;
	int	i2;

	i1 = 0;
	i2 = 0;
	while (dst[i1])
		i1++;
	while (src[i2])
	{
		dst[i1] = src[i2];
		i1++;
		i2++;
	}
	dst[i1] = '\0';
	return (dst);
}
