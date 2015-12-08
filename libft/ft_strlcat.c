/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 08:58:29 by cbarbisa          #+#    #+#             */
/*   Updated: 2013/11/30 11:16:17 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	while (dst[i1])
		i1++;
	if (size <= i1)
		return (size + ft_strlen(src));
	while (i1 + 1 < size && src[i2])
	{
		dst[i1] = src[i2];
		i1++;
		i2++;
	}
	dst[i1] = '\0';
	return (i1 - i2 + ft_strlen(src));
}
