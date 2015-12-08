/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 10:41:27 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/14 12:08:15 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t		i;
	char		*string1;
	const char	*string2;

	i = 0;
	string1 = (char*)s1;
	string2 = (char*)s2;
	while (i != n)
	{
		string1[i] = string2[i];
		i++;
	}
	return (string1);
}
