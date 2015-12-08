/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 14:26:22 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/18 19:45:21 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_memalloc(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if ((int)size <= 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * size);
	while (i < size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
