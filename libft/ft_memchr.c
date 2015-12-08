/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 11:00:50 by cbarbisa          #+#    #+#             */
/*   Updated: 2013/11/30 11:11:39 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	l;

	l = c;
	string = (unsigned char *)s;
	while (n--)
	{
		if (*string == l)
			return (string);
		string++;
	}
	return (NULL);
}
