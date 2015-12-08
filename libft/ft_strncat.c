/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 08:58:29 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/01/02 15:01:59 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	while (dst[i1])
		i1++;
	while (i2 < n && src[i2])
	{
		dst[i1] = src[i2];
		i1++;
		i2++;
	}
	dst[i1] = '\0';
	return (dst);
}
