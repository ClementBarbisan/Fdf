/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 11:30:49 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/14 11:51:14 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t		i;
	char		*string1;
	const char	*string2;
	char		*tmp;

	i = 0;
	string1 = (char *)s1;
	string2 = (const char *)s2;
	tmp = ft_memalloc(ft_strlen(s2) + 1);
	while (string2[i])
	{
		tmp[i] = string2[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		string1[i] = tmp[i];
		i++;
	}
	return (string1);
}
