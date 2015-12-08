/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:47:28 by cbarbisa          #+#    #+#             */
/*   Updated: 2014/04/14 11:57:54 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	if (!s || !f)
		return (result);
	result = ft_memalloc(ft_strlen(s) + 1);
	while (s[i])
	{
		result[i] = (char)s[i];
		result[i] = f(result[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
