/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 14:57:16 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/14 13:13:09 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

static char	*ft_split(char const *s, char c, int *k)
{
	char	*result;
	int		i;
	int		l;

	l = 0;
	i = *k;
	while (s[*k] && s[*k] != c)
		(*k)++;
	result = ft_memalloc(*k - i + 1);
	while (i != *k && s[i] != c)
	{
		result[l] = s[i];
		l++;
		i++;
	}
	result[l] = '\0';
	return (result);
}

char		**ft_strsplit(char const *s, char c)
{
	int		k;
	int		j;
	char	**result;

	k = 0;
	j = 0;
	result = NULL;
	if (!s || s[0] == '\0')
		return (result);
	result = (char **)malloc(sizeof(char*) * (ft_strlen(s) + 1));
	while (s[k])
	{
		if (s[k] && s[k] == c)
			k++;
		if (s[k] && s[k] != c)
		{
			result[j] = ft_split(s, c, &k);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}
