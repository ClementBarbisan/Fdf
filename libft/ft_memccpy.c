/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 12:00:03 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/14 12:20:28 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t	i;
	char	*string1;
	char	*string2;

	i = 0;
	string1 = (char*)s1;
	string2 = (char*)s2;
	while (i != n)
	{
		string1[i] = string2[i];
		if (string2[i] == c)
			return (string1 = &string1[i + 1]);
		i++;
	}
	return (NULL);
}
