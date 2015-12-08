/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 16:24:44 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/18 19:21:23 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char			*str1;
	char			*str2;
	size_t			i;
	unsigned int	result;

	i = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	result = 0;
	if (n == 0)
		return (result);
	while (*str1 == *str2 && i + 1 < n && *str1 != '\0' && *str2 != '\0')
	{
		str1++;
		str2++;
		i++;
	}
	return (*str1 - *str2);
}
