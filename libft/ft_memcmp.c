/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 11:15:43 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/14 12:08:36 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	string1;
	unsigned char	string2;

	if (!n)
		return (0);
	while (n--)
	{
		string1 = *(unsigned char *)s1;
		string2 = *(unsigned char *)s2;
		if (string1 != string2)
			return (string1 - string2);
		s1++;
		s2++;
	}
	return (0);
}
