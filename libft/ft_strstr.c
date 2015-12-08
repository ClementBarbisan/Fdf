/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 17:20:09 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/14 12:14:26 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static int		ft_search(const char *str, const char *to_find, int len)
{
	int		size;

	size = 0;
	while (to_find[size])
		size++;
	while (size > 0)
	{
		if (to_find[size - 1] == str[len + size - 1])
			size--;
		else
			return (0);
	}
	return (1);
}

char			*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	char	*result;

	i = 0;
	if (ft_strlen(s2) == 0)
		return (result = (char*)s1);
	while (s1[i])
	{
		if (s1[i] == s2[0])
		{
			if (ft_search(s1, s2, i))
				return (result = (char*)&s1[i]);
		}
		i++;
	}
	return (NULL);
}
