/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 14:54:24 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/14 12:09:29 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

static char		*ft_join_s(const char *s)
{
	char	*result;

	result = ft_memalloc(ft_strlen(s) + 1);
	while (*s)
	{
		*result = *s;
		result++;
		s++;
	}
	*result = '\0';
	return (result);
}

static char		*ft_join_s1_s2(const char *s1, const char *s2)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (*s1)
	{
		result[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		result[i] = *s2;
		i++;
		s2++;
	}
	result[i] = '\0';
	return (result);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_join_s(s2));
	else if (!s2)
		return (ft_join_s(s1));
	return (ft_join_s1_s2(s1, s2));
}
