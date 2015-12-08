/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:52:35 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/01/21 09:36:55 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <string.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}
