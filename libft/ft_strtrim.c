/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 11:43:46 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/05/26 16:15:55 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

static char	*ft_space(char *result, char const *s, int i1, int i2)
{
	while (s[i1] == '\0' && i1 >= 0)
	{
		result[i2] = '\0';
		i1--;
		i2--;
	}
	while ((s[i1] == ' ' || s[i1] == '\n' || s[i1] == '\t') && i1 >= 0)
	{
		result[i2] = '\0';
		i2--;
		i1--;
	}
	return (result);
}

char		*ft_strtrim(char const *s)
{
	char	*result;
	int		i1;
	int		i2;

	i1 = 0;
	while (s != NULL && s[i1] != '\0' && (s[i1] == ' '\
				|| s[i1] == '\n' || s[i1] == '\t'))
		i1++;
	i2 = ft_strlen(s) - i1;
	if (i2 > 0)
		result = (char *)malloc(sizeof(char) * (i2 + 1));
	else
		return (NULL);
	i2 = 0;
	while (s[i1])
	{
		result[i2] = s[i1];
		i1++;
		i2++;
	}
	result[i2] = '\0';
	result = ft_space(result, s, i1, i2);
	return (result);
}
