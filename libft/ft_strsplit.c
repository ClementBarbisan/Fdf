/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 14:57:16 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/15 11:05:14 by cbarbisa         ###   ########.fr       */
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
	result = malloc(sizeof(char) * (*k - i + 1));
	while (i != *k && s[i] != c)
	{
		result[l] = s[i];
		l++;
		i++;
	}
	result[l] = '\0';
	return (result);
}

int			search_char(char const *line, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == c && line[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
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
	result = (char **)malloc(sizeof(char*) * (search_char(s, c) + 1));
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
